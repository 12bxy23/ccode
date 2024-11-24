#include <stdio.h>
/*
 99乘法表
 */

int main(void)
{
	int i, j;

	for (i = 1; i < 10; i++) {
		// i 每一行
		for (j = 1; j <= i; j++) {
			// %2d就是输出的整型数占两个字符宽度，不够补空格
			printf("%d * %d = %2d ", j, i, j * i);
		}
		printf("\n");
	}

	return 0;
}

