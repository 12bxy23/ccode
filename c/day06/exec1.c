#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 定义一个由20个整型变量组成的数组，值随机
 求出这个数组中有多少个质数

 将这个数组中的最大最小值交换

 */
#define N	20

int is_primer(int n);

int main(void)
{
	int arr[N];
	int i;
	int cnt = 0;
	int max, min;
	int t;

	srand(time(NULL));

	for (i = 0; i < N; i++) {
		arr[i] = rand() % 100;
	
		// 判断
		if (is_primer(arr[i]))
			cnt ++;

		printf("%d ", arr[i]);
		// 找到最大最小值
		if (i == 0) {
			max = min = 0; // 假定第一个元素是最大值 最小值
		} else {
			if (arr[i] > arr[max])
				max = i;
			if (arr[i] < arr[min])
				min = i;
		}
	}
	printf("\n");
	printf("有%d个质数\n", cnt);

	// 最大值在max 最小值在min
	// 交换
	t = arr[max];
	arr[max] = arr[min];
	arr[min] = t;

	// 遍历
	for (i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

int is_primer(int n)
{
	int i;

	if (n < 2)
		return 0;
	
	for (i = 2; i <= n / 2; i++) {
		if (n % i == 0)
			return 0;
	}

	return 1;
}



