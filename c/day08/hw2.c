#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M	4
#define N	5

void swap2num(int *a, int *b);
void max_behind(int *arr, int n);
void bubble_sort(int *arr, int n);

int main(void)
{
	int arr[M][N];
	int i, j;

	srand(time(NULL));
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			arr[i][j] = rand() % 100;
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	// 取得每一个一维数组
	for (i = 0; i < M; i++) {
		// max_behind(arr[i], N);
		bubble_sort(arr[i], N);
	}

	printf("*****************\n");

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}

/*
 将一维数组的最大值放到最后
 */
void max_behind(int *arr, int n)
{
	int max;
	int i;
	int t;

	for (max = 0, i = 1; i < n; i++) {
		if (arr[max] < arr[i])
			max = i;
	}
	if (max != n - 1) {
		swap2num(arr + max, arr + n - 1);
	}
}

void bubble_sort(int *arr, int n)
{
	int i, j;
	int t;

	for (i = 0; i < n - 1; i ++) {
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j+1]) {
				swap2num(arr + j, arr + j + 1);	
			}
		}
	}
}

/*交换两个整型变量*/
void swap2num(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}




