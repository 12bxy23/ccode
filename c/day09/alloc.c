#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// int *arr = (int *)malloc(40); // 随机值
	int *arr = (int *)calloc(10, sizeof(int)); // 0
	int i;

	for (i = 0; i < 10; i++)
		arr[i] = i + 1;
	for (i = 0; i < 10; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// 再存10个元素
	arr = realloc(arr, 40 + 40);
	
	for (i = 10; i < 20; i++)
		arr[i] = i+1;

	for (i = 0; i < 20; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// 保留前5个
	arr = realloc(arr, 5 * sizeof(int));
	for (i = 0; i < 5; i++)
		printf("%d ", arr[i]);
	printf("\n");

	free(arr);
	arr = NULL;// !!!!!!

	return 0;
}

