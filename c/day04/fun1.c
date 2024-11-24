#include <stdio.h>

// 全局变量 存储在bss段，值一定是0
int global;

int test(int a, int b);
inline int max2num(int a, int b);

int main(void)
{
	// 局部变量 存储在stack 值随机
	auto int var; 
	// 只读变量
	const int num = 10;
	// 防止编译器优化的
	volatile int v = 100;

	// num ++;
	printf("num:%d\n", num);

	printf("var:%d, global:%d\n", var, global);

	printf("%d\n", test(1, 2));
	printf("%d\n", test(1, 2));
	printf("%d\n", test(1, 2));
	printf("%d\n", test(1, 2));

	printf("max:%d\n", max2num(100, 300));

	return 0;
}

int test(int a, int b)
{
	// 局部静态变量，已经初始化了，data段 生存周期是整个进程
	static int s = 1;

	printf("a:%d, b:%d\n", a, b);
	printf("test global:%d\n", global);

	a ++, b++;

	return s++;
}

// 内联/内建函数, 内联函数没有额外的函数地址，函数调用的时候仅仅是代码的替换
// 仅仅适用于函数功能及其简单的函数
int max2num(int a, int b)
{
	return a > b ? a : b;
}



