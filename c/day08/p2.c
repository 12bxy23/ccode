#include <stdio.h>

int deal_arr(int *arr, int n, int *max, int *min, int *avg);
int main(void)
{
	int a[] = {1,6,8,9,2,5,4,7,9};
	int maxnum, minnum, avgvalue;

	deal_arr(a, sizeof(a) / sizeof(int), &maxnum, &minnum, &avgvalue);
	printf("maxnum:%d, minnum:%d, avgvalue:%d\n", \
			maxnum, minnum, avgvalue);

	return 0;
}

/*
 返回整型数组的最大值，最小值，平均值
 */
int deal_arr(int *arr, int n, int *max, int *min, int *avg)
{
	int i;
	*max = *min = arr[0];
	int sum = arr[0];

	for (i = 1; i < n; i++) {
		if (arr[i] > *max)
			*max = arr[i];
		if (arr[i] < *min)
			*min = arr[i];
		sum += arr[i];
	}
	*avg = sum / n;

	return 0;
}

