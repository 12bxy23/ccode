#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "tbf.h"

// 抽象数据类型
typedef struct {
	int token; // 令牌
	int cps; // 速率
	int burst; // 上限 
}tbf_t;

// 令牌桶库结构
static tbf_t *jobs[TBFMAX] = {};
static int inited = 0;

static int __get_free_pos(void);
static void sig_moduler_load(void);

int tbf_init(int cps, int burst)
{
	tbf_t *me;
	int pos;

	/*
	 当第一次调用init启动信号SIGALRM
	 信号周期性产生，信号处理函数将所有令牌桶库中不空闲的位置对应积攒令牌
	 */
	if (!inited) {
		sig_moduler_load(); // 注册信号的行为，定闹钟
		inited = 1;
	}

	me = malloc(sizeof(tbf_t));
	if (NULL == me)
		return -1;
	me->token = 0;
	me->cps = cps;
	me->burst = burst;

	pos = __get_free_pos();
	if (pos == -1) {
		free(me);
		return -1;
	}
	jobs[pos] = me;

	return pos;
}

// 找到库中空闲的指针
static int __get_free_pos(void) 
{
	int i;

	for (i = 0; i < TBFMAX; i++)
		if (jobs[i] == NULL)
			return i;
	
	return -1;
}

static void alarm_handler(int s)
{
	int i;
	// 管理令牌桶库
	alarm(1);

	for (i = 0; i < TBFMAX; i++) {
		if (jobs[i]) {
			// 这里有令牌桶 需要积攒令牌
			jobs[i]->token += jobs[i]->cps;
			if (jobs[i]->token > jobs[i]->burst)
				jobs[i]->token = jobs[i]->burst;
		}
	}

}

static void sig_moduler_load(void)
{
	// 注册信号的行为
	signal(SIGALRM, alarm_handler);
	// 定闹钟
	alarm(1);
}

int tbf_fetch_token(int tb, int ntokens)
{
	int ret;

	if (tb < 0 || tb >= TBFMAX)
		return -1;
	while (jobs[tb]->token <= 0)
		pause(); // 如果没有令牌则等信号 通知法

	if (jobs[tb]->token < ntokens) {
		ret = jobs[tb]->token;
	} else {
		ret = ntokens;
	}
	jobs[tb]->token -= ret;

	return ret;
}

void tbf_destroy(int tb)
{
	if (tb < 0 || tb >= TBFMAX)
		return ;
	free(jobs[tb]);
	jobs[tb] = NULL;
}

