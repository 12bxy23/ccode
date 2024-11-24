/*
 12：随机生成一个五位以内的数，然后输出该数共有多少位，每位分别是什么
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int num;

	srand(time(NULL));

	// 五位以内的数
	num = rand() % 100000;
	printf("num:%d\n", num);
	while (num) {
		printf("%d ", num % 10);
		num /= 10; // 缩小10倍
	}
	printf("\n");

	return 0;
}

