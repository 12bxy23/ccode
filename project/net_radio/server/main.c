#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>

#include "./thread_pool/pool.h"
#include "media_lib.h"
#include "../proto/net_radio_proto.h"

#define DEBUG_MLIB_CHN_LIST

// 结构为了将频道列表数组作为任务函数的参数传递
typedef struct {
	struct mlib_st *mlib;
	int chn_nr;
}my_chn_list_t;

static int udp_socket;
static struct sockaddr_in groupaddr;

static int sock_init(void);
static void *task_send_chn_data(void *arg);
static void *task_send_chn_list(void *arg);
int main(void)
{
	threadpool_t *mypool;
	my_chn_list_t mychn = {NULL, 0};
	int i;

	// 初始化套接字
	sock_init();

	// 初始化线程池
	mypool = threadpool_init(MAX_CHN_NR, 3, MAX_CHN_NR);

	// 获取频道列表 
	mlib_get_chn_list(&mychn.mlib, &mychn.chn_nr);
	printf("[%d]debug...\n", __LINE__);
#ifdef DEBUG_MLIB_CHN_LIST
	for (i = 0; i < mychn.chn_nr; i++) {
		printf("%d %s\n", (mychn.mlib)[i].chnid, (mychn.mlib)[i].descr);
	}
#endif

	// 添加发送频道列表的任务(函数)
	threadpool_add_task(mypool, task_send_chn_list, &mychn);

	// 有多少个频道，就要并发多少个线程，同时发送对应频道的数据
	// 并发由线程池完成的，main线程将多线程调用的函数添加的线程池的工作队列
	for (i = 0; i < mychn.chn_nr; i++) {
		threadpool_add_task(mypool, task_send_chn_data, &((mychn.mlib)[i].chnid));	
	}

	while (1)
		pause();

	return 0;
}

/*
   初始化套接字
   socket()
   将套接字设置为组播setsockopt(2)打开组播功能
 */
static int sock_init(void)
{
	struct ip_mreqn imr;

	// 创建套接字
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == udp_socket) {
		perror("socket()");
		return -1;
	}
	// 设置多播
	inet_aton(GROUP_IP, &imr.imr_multiaddr);
	inet_aton("0.0.0.0", &imr.imr_address);
	imr.imr_ifindex = if_nametoindex("ens33");
	if (-1 == setsockopt(udp_socket, IPPROTO_IP, IP_MULTICAST_IF, &imr, sizeof(imr))) {
		perror("setsockopt()");
		close(udp_socket);
		return -1;
	}
	// 初始化目的地址
	groupaddr.sin_family = AF_INET;
	groupaddr.sin_port = htons(RCV_PORT);
	inet_aton(GROUP_IP, &groupaddr.sin_addr);

	return 0;
}

/*
 发送频道列表
 */
static void *task_send_chn_list(void *arg)
{
	// 周期性发送频道列表
	// 发送到多播组--->数据类型遵循net_radio_proto.h中的整个列表类型
	struct chn_list_st *sndlist = NULL;
	struct chn_list_entry *listentry = NULL;
	my_chn_list_t *chnlist = arg;
	int i;
	int entry_len = 0;
	int all_len = 0;

	printf("[%d]debug...\n", __LINE__);
	// 每一个频道列表组成一个完整的包 struct chn_list_st
	sndlist = malloc(MAX_MSG);
	if (NULL == sndlist) {
		return NULL;
	}
	sndlist->chnid = CHN_LIST_ID;
	all_len = sizeof(sndlist->chnid);
	for (i = 0; i < chnlist->chn_nr; i++) {
		entry_len = sizeof(int8_t) + sizeof(int8_t)	+ strlen((chnlist->mlib)[i].descr) + 1;
		listentry = malloc(entry_len);
		// if error
		listentry->chnid = (chnlist->mlib)[i].chnid; // 当前频道号
		listentry->len = entry_len; // 频道包大小
		strcpy(listentry->descr, (chnlist->mlib)[i].descr);
		// 将单个频道的数据包copy到整个频道列表包中
		if (all_len + entry_len >= MAX_MSG)
			break;
		memcpy((char *)sndlist + all_len, listentry, entry_len);
		all_len += entry_len;
		free(listentry);
		listentry = NULL;
	}
	printf("[%d]debug...\n", __LINE__);
	// sndlist多少个字节 all_len

	while (1) {
		sendto(udp_socket, sndlist, all_len, 0, (struct sockaddr *)&groupaddr, sizeof(groupaddr));
		sleep(1);	
	}

	return NULL;
}

/*
 发送频道数据的函数
 */
static void *task_send_chn_data(void *arg)
{
	int8_t my_chn_id = *((int8_t*)arg);
	// arg就是频道号
	// mlib_read_chn_data();
	struct chn_data_st *snd_data_p = NULL;
	ssize_t cnt;
	
	snd_data_p = malloc(MAX_MSG);
	
	snd_data_p->chnid = my_chn_id;
	while (1) {
		cnt = mlib_read_chn_data(my_chn_id, snd_data_p->msg, MAX_MSG - sizeof(int8_t));
		if (-1 == cnt) {
			fprintf(stderr, "%d频道出错\n", my_chn_id);
			return NULL;
		}
		sendto(udp_socket, snd_data_p, cnt + sizeof(int8_t), 0, (struct sockaddr *)&groupaddr, sizeof(groupaddr));
		// 流量控制
		sleep(1);
	}
}


