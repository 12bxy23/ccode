/*
 读入一个整型数,判断这个数的奇偶性
 分析：
 	能被2整除的数就是偶数 n % 2 == 0
 */
#include <stdio.h>

int main(void)
{
	int n;

	// 语法规范:,后隔空格，双目运算符前后空格
	scanf("%d", &n);

	if (n % 2 == 0) {
		printf("这是一个偶数\n");
	} else {
		printf("这是一个奇数\n");
	}

	return 0;
}

