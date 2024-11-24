#ifndef __TBF_H__
#define __TBF_H__

/*
 令牌桶库
 	所谓库，就是不止一个，大量
 */
#define TBFMAX	1024

/*
 	创建令牌桶
 	cps:速率
	burst:上限
	return: 所在令牌桶库的索引值---》桶描述符
 */
int tbf_init(int cps, int burst);

// 取令牌
/*
tb:桶描述符
ntokens:要取得的令牌数
return:取到的令牌数
 */
int tbf_fetch_token(int tb, int ntokens);

// 销毁指定令牌桶
void tbf_destroy(int tb);

// 销毁令牌桶库
void tbf_destroy_all(void);

#endif

