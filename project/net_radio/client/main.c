#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/if.h>
#include "../proto/net_radio_proto.h"

#define BUFSIZE	4096

static void sig_handler(int s)
{

}

static int cp_file(int rfd, int wfd);

int main(int argc, char *argv[])
{
	int fd;
	int pfd[2] = {};
	pid_t pid;
	int udp_socket;
	struct chn_list_st *rcv_list;
	struct chn_list_entry *entry;
	struct chn_data_st *rcv_data;	
	union chn_msg_st *rcv_msg;
	struct sockaddr_in myaddr; // man 7 ip
	struct ip_mreqn imr;
	int len, choose;

	// sigaction
	signal(SIGINT, sig_handler);

	if (-1 == pipe(pfd)) {
		perror("pipe()");
		exit(1);
	}
	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		goto ERROR;
	}

	if (0 == pid) {
		// 读管道
		close(pfd[1]);
		dup2(pfd[0], 0);
		pause(); // 等待信号到来
		
		// 用文本文件调试
		char buf[BUFSIZE] = {};
		int cnt;
		while (1) {
			cnt = read(0, buf, BUFSIZE);	
			if (-1 == cnt) {
				perror("read()");
				exit(1);
			} else if (0 == cnt) {
				exit(0);
			}
			write(1, buf, cnt);
		}

#if 0
		execl("/usr/bin/mplayer", "mplayer", "-", NULL);
		perror("execl()");
		exit(1);
#endif
	}
	
	close(pfd[0]);
	// 初始化套接字
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == udp_socket) {
		perror("socket()");
		exit(1);
	}

	// 被动端需要bind地址
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(RCV_PORT);
	inet_aton("0.0.0.0"/*INADDR_ANY*/, &myaddr.sin_addr);
	if (-1 == bind(udp_socket, (struct sockaddr *)&myaddr, sizeof(myaddr))) {
		perror("bind()");
		goto ERROR;
	}

	// 加入多播组
	inet_aton(GROUP_IP, &imr.imr_multiaddr);
	// 注意INADDR_ANY不是字符串，是uint32_t整型数
	inet_aton("0.0.0.0", &imr.imr_address);
	// 虚拟网卡的索引值，索引名转换为值if_nametoindex(3)
	imr.imr_ifindex = if_nametoindex("ens33");
	if (-1 == setsockopt(udp_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr, sizeof(imr))) {
		perror("setsockopt()");
		goto ERROR;
	}

	rcv_msg = malloc(MAX_MSG);
	if (NULL == rcv_msg)
		goto ERROR;
	while (1) {
		len = recvfrom(udp_socket, rcv_msg, MAX_MSG, 0, NULL, NULL);
		if (-1 == len) {
			if (errno == EINTR)
				continue;
			perror("recvfrom()");
			goto ERROR;
		}
		if (0 == len)
			break;
		// 如果不是列表
		if (rcv_msg->chnid == CHN_LIST_ID)
			break;
	}
	// 接收到了列表--->打印列表
	rcv_list = (void *)rcv_msg;
	for (entry = (void *)((char *)rcv_list + sizeof(rcv_list->chnid)); (char *)entry - (char *)rcv_list < len; entry = (void *)((char *)entry + entry->len)) {
		printf("%d %s\n", entry->chnid, entry->descr);	
		sleep(1);
	}
	// 选择
	printf("请选择频道:");
	scanf("%d", &choose);

	kill(pid, SIGINT);

	// 接受频道数据
	rcv_data = (void *)rcv_msg;
	while (1) {
		memset(rcv_data, '\0', MAX_MSG);
		len = recvfrom(udp_socket, rcv_data, MAX_MSG, 0, NULL, NULL);
		if (-1 == len) {
			if (errno == EINTR)
				continue;
			perror("recvfrom()");
			goto ERROR;
		}
		if (0 == len)
			break;
		// 是否是选择的频道号
		if (rcv_data->chnid != choose)
			continue;
		write(pfd[1], rcv_data->msg, len - sizeof(rcv_data->chnid));
	}
	printf("您所选择的频道已经关闭，拜拜!!!\n");

	free(rcv_msg);
	rcv_msg = NULL;
	close(udp_socket);
	close(pfd[1]);

	wait(NULL);

	exit(0);
ERROR:
	close(pfd[0]);
	close(pfd[1]);

	exit(1);
}

