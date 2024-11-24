#ifndef __MEDIA_LIB_H__
#define __MEDIA_LIB_H__

#define MEDIA_PATH			"/home/zhang/media"
#define MEDIA_MAX_CHN_NR	200

/*
 媒体库模块需要的数据类型
 提供的API
 */
struct mlib_st {
	int8_t chnid; // 频道号
	char *descr; // 频道描述的起始地址
};

// API
/*
 获取频道列表
 *mlib:频道列表结构体数组的起始地址
 *chn_nr:频道个数
return:成功与否状态
 */
int mlib_get_chn_list(struct mlib_st **mlib, int *chn_nr);

/*
读取对应频道数据的 
chnid:频道号
buf:存放读到的数据
size:要读的字节个数
return:读到的字节个数
 */
ssize_t mlib_read_chn_data(int8_t chnid, void *buf, size_t size);

#endif

