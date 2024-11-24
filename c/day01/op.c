#include <stdio.h>

int main(void)
{
	int m, n; // 定义两个整型变量，分别是m和n

	scanf("%d%d", &m, &n);

	// printf("%d %% %d == %d\n", m, n, m % n);
	// 位运算
	printf("m左移1位:%d\n", m << 1);
	printf("n右移1位:%d\n", n >> 1);

	printf("%d & %d = %d\n", m, n, m & n);
	printf("%d | %d = %d\n", m, n, m | n);
	printf("%d ^ %d = %d\n", m, n, m ^ n);
	printf("~%d = %d\n", m, ~m);

	// 将一个整型数的某一位置1，清0

	return 0;
}

