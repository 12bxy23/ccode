#ifndef __NETRADIO_PROTO_H__
#define __NETRADIO_PROTO_H__

/*
 server client协议
 UDP组播
 组播地址+接收端口
 数据类型
 */
#define GROUP_IP	"224.2.2.2"
#define RCV_PORT	6789	
#define MAX_CHN_NR	200
#define MIN_CHN_ID	1
#define MAX_CHN_ID	((MIN_CHN_ID) + (MAX_CHN_NR) - 1)
#define CHN_LIST_ID	0
#define MAX_MSG		512

// 频道列表
// 单个频道列表结构
struct chn_list_entry {
	int8_t chnid; // > 0
	int8_t len; // 自述长度,描述当前结构的字节大小
	char descr[1]; // 变长结构体
}__attribute__((packed));

// 整个频道列表结构
struct chn_list_st {
	int8_t chnid; // MUST BE 0
	struct chn_list_entry entrys[1]; // 变长结构体，有多少个频道，就多少个结构
	// 当变长结构体中包含变成结构体，为了访问数据方便，可以在子结构体中自述长度
}__attribute__((packed));


// 频道数据
struct chn_data_st {
	int8_t chnid; // MIN_CHN_ID ~MAX_CHN_ID
	char msg[1];
}__attribute__((packed));

// 共用体
union chn_msg_st {
	int8_t chnid;
	struct chn_list_st chnlist;
	struct chn_data_st chndata;
};

#endif

