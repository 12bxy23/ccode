#include <stdio.h>

int is_primer(int num);

int main(void)
{
	int cnt = 0; // 计数器
	int i;

	for (i = 100; i <= 1000; i++)
		if (is_primer(i))
			cnt ++;
	printf("100~1000之间有%d个质数\n", cnt);

	return 0;
}

// 判断是否为质数
/*
 num就是待计算的数值
 返回值为1就表示是质数，返回0就表示不是质数
 */
int is_primer(int num)
{
	int i;

	if (num < 2)
		return 0;

	for (i = 2; i < num; i++) {
		if (num % i == 0)
			break;
	}

	return i == num; // 说明for循环的终止是由于循环条件不满足
}


