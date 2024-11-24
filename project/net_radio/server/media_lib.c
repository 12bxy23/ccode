#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "media_lib.h"

#define BUFSIZE	256

// 内部结构，解析一次频道目录所要获取的所有内容
struct chn_context_st {
	struct mlib_st mlib_list; // 频道列表
	// 对应存储频道的音频文件路径
#if 0
	char **mp3_path; // 存储当前频道所有音频文件路径的指针数组的起始地址
	int mp3_nr; // 音频个数
#endif
	glob_t mp3_path; // 音频路径存mp3_path.gl_pathv指针数组中
	int mp3_index; // mp3_path.gl_pathv数组当前读的音频的索引
	int mp3_fd; // 当前第mp3_index+1个音频对应的文件描述符
	int mp3_pos; // 读到了第mp3_index+1个音频文件的位置是pos
};

// 每一个频道都有一个struct chn_context_st结构,最多MAX_CHN_NR频道,频道号与对应所在数组的下标值相等
static struct chn_context_st *chns[MEDIA_MAX_CHN_NR + 1];

/*
 给定某一个频道的路径
 媒体库-->MEDIA_PATH
 例如"MEDIA_PATH/music"
 */
static struct chn_context_st *__get_chn_context(const char *path)
{
	FILE *fp;
	char buf[BUFSIZE] = {};
	struct chn_context_st *mychn = NULL;
	static int cur_chn_id = 1;
	size_t len;
	int ret;
	glob_t res;

	strncpy(buf, path, BUFSIZE);
	// 频道描述路径
	strncat(buf, "/descr.txt", BUFSIZE - strlen(path));
	
	// 打开描述文件并读出频道描述
	fp = fopen(buf, "r");	
	if (NULL == fp) {
		// 没有描述文件 --->不是有效频道
		return NULL;
	}
	// 当前频道结构开辟存储空间
	mychn = malloc(sizeof(struct chn_context_st));
	if (NULL == mychn) {
		fclose(fp);
		return NULL;
	}
	len = 0;
	mychn->mlib_list.descr = NULL;
	if (-1 == getline(&mychn->mlib_list.descr, &len, fp)) {
		// 描述文件是空的
		fclose(fp);
		free(mychn);
		return NULL;
	}
	// 存储当前频道下的所有音频文件路径
	strncpy(buf, path, BUFSIZE);
	strncat(buf, "/*.mp3", BUFSIZE - strlen(path));
	// buf--->"/home/zhang/media/music/*.mp3"
	memset(&mychn->mp3_path, '\0', sizeof(glob_t));
	ret = glob(buf, 0, NULL, &mychn->mp3_path);
	// 段错误
	if (GLOB_NOMATCH == ret) {
		// 该频道没有音频, 只有描述
		printf("描述是:%s的频道没有音频的\n", mychn->mlib_list.descr);
		fclose(fp);
		free(mychn);
		return NULL;
	}

	// 该频道是有效频道---》分配频道id
	mychn->mlib_list.chnid = cur_chn_id++;

	// 当前频道对应的存储所有音频路径的指针数组的下标
	mychn->mp3_index = 0;
	mychn->mp3_pos = 0;
	// 打开第一个要读的文件
	mychn->mp3_fd = open(((mychn->mp3_path).gl_pathv)[mychn->mp3_index], O_RDONLY);

	return mychn;
}

int mlib_get_chn_list(struct mlib_st **mlib, int *chn_nr)
{
	DIR *dp;
	struct dirent *entry;
	char buf[BUFSIZE] = {};
	struct chn_context_st *context;
	int i;
	int len;

	// 解析媒体库得到每一个频道的路径
	// MEDIA_PATH-->"/home/zhang/media"
	// CHN_PATH--->"/home/zhang/media/music"
	dp = opendir(MEDIA_PATH);
	if (NULL == dp) {
		perror("opendir()");
		return -1;
	}
	i = 0;
	while (1) {
		entry = readdir(dp);	
		if (NULL == entry)
			break;
		// entry->d_name // 文件名
		// name--->path
		memset(buf, '\0', BUFSIZE);
		len = BUFSIZE;
		strncpy(buf, MEDIA_PATH, len);
		len -= (strlen(buf) + 1);
		strncat(buf, "/", len);
		len -= 1;
		strncat(buf, entry->d_name, len);
		// buf就是某一个频道的路径
		context = __get_chn_context(buf);
		if (NULL == context)
			continue;
		*mlib = realloc(*mlib, (i + 1) * sizeof(struct mlib_st));
		if (NULL == *mlib)
			return -1;
		(*mlib)[i] = context->mlib_list;
		chns[context->mlib_list.chnid] = context;
		i++;
	}
	*chn_nr = i; // 频道个数

	return 0;
}

// 关闭当前，打开下一个
static int __open_next(struct chn_context_st *mychn)
{
	close(mychn->mp3_fd);
	
	mychn->mp3_index++;
	if (mychn->mp3_index == mychn->mp3_path.gl_pathc) {
		// 循环
		mychn->mp3_index = 0;
	}
	mychn->mp3_fd = open((mychn->mp3_path.gl_pathv)[mychn->mp3_index], O_RDONLY);
	if (-1 == mychn->mp3_fd) {
		perror("open()");
		return -1;
	}
	mychn->mp3_pos = 0;

	return 0;
}

ssize_t mlib_read_chn_data(int8_t chnid, void *buf, size_t size)
{
	// chns[chnid]就是chnid频道对应的频道结构
	struct chn_context_st *mychn = chns[chnid];
	ssize_t cnt;
	// 所有的文件路径mychn->mp3_path.gl_pathv
	while (1) {
		cnt = pread(mychn->mp3_fd, buf, size, mychn->mp3_pos);
		if (cnt == -1) {
			perror("pread()");
			return -1;
		} else if (cnt == 0) {
			// 当前音频读完了，关闭当前文件，打开下一个
			// 下一个文件的路径(mychn->mp3_path.gl_pathv)[mychn->mp3_index + 1]
			__open_next(mychn);
		} else
			break;
	}

	mychn->mp3_pos += cnt;

	return cnt;
}

