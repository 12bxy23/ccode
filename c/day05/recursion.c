#include <stdio.h>

int sumn(int n);
int fib(int n);

int main(void)
{
	int i;

	for (i = 0; i <= 10; i++) {
		printf("%d\n", sumn(i));
	}

	for (i = 1; i <= 20; i++) {
		printf("%d\n", fib(i));
	}

	return 0;
}

// 用递归的方式计算n的前n项和
int sumn(int n)
{
	if (n < 0)
		return -1;

	// 终止条件
	if (0 == n)
		return 0;

	// 递归点
	return n + sumn(n - 1);
}

/*
 求斐波那契数列的第n项
 */
int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	if (n < 1)
		return -1;
	return fib(n - 1) + fib(n - 2);
}










