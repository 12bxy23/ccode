#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N	20

int main(void)
{
	int arr[N] = {};
	int i, j;
	int t;

	srand(time(NULL));

	for (i = 0; i < N; i++) {
		arr[i] = rand() % 100;
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("********倒序输出********\n");
	for (i = N - 1;  i >= 0; i--) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	for (i = 0; i < N; i++) {
		if (arr[i] % 2)	 {
			// 前面有奇数
			for (j = N-1; j > i; j--) {
				if (arr[j] % 2 == 0)
					break;
			}
			// 两种循环终止的可能
			if (j == i) {
				// 后面没有偶数了
				break;
			} else {
				// 下标为j的这个元素是偶数
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}

	for (i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");


	return 0;
}

