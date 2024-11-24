#include <stdio.h>
#include "my.h"
#include "my.h"
#include "my.h"
#include "my.h"
#include "my.h"

// 例如之前实现日历小工程的时候的基础年份1970是一个常量
/*
 宏定义会在gcc预处理阶段，将程序中所有出现BASEYEAR的位置用1970替换
 优势:
 	将值赋予一定的含义，BASEYEAR相对于1970可读性更高
	在程序中返回出现这个值的时候，如果要修改这个值，那么使用宏可以值修改宏的值
 注意:
 	宏不能换行
	不能有分号
	只适合简单的功能
 */
#define BASEYEAR	1970

// 宏可以是表达式, 例如表达一年有多少s
#define SECONDYEAR	(365 * 24 * 60 * 60UL)

// 宏还可以是函数--->宏函数 宏函数是么有地址的，所有的预处理指令包括宏函数都仅仅做替换
// 宏函数的参数必须加()
#define MAX2NUM(x, y) ((x) > (y) ? (x) : (y))

#define SQUEAR(x) (x) * (x)

// ## 表示拼接 
#define CONN(x) x##x

// 写一个宏实现两个数
// typeof(x) 获取x的类型 如果x是int typeof(x) 就相当于int的交换
#define SWAP(x, y) \
	do {\
		typeof(x) t; \
		t = x; \
		x = y; \
		y = t; \
	} while(0)

int main(void)
{
	int year = 1990;
	int i, y;
	float a = 1.2, b = 3.5;
	
	for (i = BASEYEAR; i < year; i++)
		printf("%d\n", i);

#if 0
	printf("%ld\n", SECONDYEAR);
#endif

	i = 5;
	printf("%d\n", SQUEAR(i + 1));

	i = 1, y = 2;

	SWAP(i, y);
	printf("i:%d, y:%d\n", i, y);

	SWAP(a, b);
	printf("a:%f, b:%f\n", a, b);

	return 0;
}

