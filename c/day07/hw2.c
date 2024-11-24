#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N	20

int main(void)
{
	int arr[N] = {};
	int i, j;
	int score[11]  = {}; // 初始化为0

	srand(time(NULL));

	for (i = 0; i < N; i++) {
		arr[i] = rand() % 101;
		printf("%d ", arr[i]);
	}
	printf("\n");

	for (i = 0; i < N; i++) {
		// arr[i] / 10就是分数舍掉个位，可能0,1,2,3,4,5,6,7,8,9,10, 用于作为score数组的下标,对应的成员变量作为该分数段的计数器
		score[arr[i] / 10] ++;
	}

	for (i = 9; i >= 0; i--) {
		if (i == 9) {
			printf("90~100:");
			for (j = 0; j < score[i] + score[i+1]; j++)
				printf("* ");
		} else {
			printf("%d~%d:", i * 10, i * 10 + 9);
			for (j = 0; j < score[i]; j++)
				printf("* ");
		}
		printf("\n");
	}

	return 0;
}

