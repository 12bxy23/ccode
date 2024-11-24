#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 什么变量就什么类型
typedef int (*cmp_t)(const void *, const void *);

void bubble_sort(void *arr, int n, int size, cmp_t cmp);
static int cmp_int(const void *data1, const void *data2);
static int cmp_string(const void *data1, const void *data2);

int main(void)
{
	int a[] = {5,1,7,9,2,3,6,8,4};
	int i;
	char *str[] = {"hello", "world", "hi", "easthome", "boys", "girls"};

	bubble_sort(a, sizeof(a) / sizeof(int), sizeof(int), cmp_int);
	for (i = 0; i < sizeof(a) / sizeof(int); i++)
		printf("%d ", a[i]);
	printf("\n");

	bubble_sort(str, sizeof(str) / sizeof(char *), sizeof(char *), cmp_string);
	for (i = 0; i < sizeof(str) / sizeof(char *); i++)
		puts(str[i]);

	return 0;
}

static int cmp_int(const void *data1, const void *data2)
{
	const int *d1 = (const int *)data1;
	const int *d2 = (const int *)data2;

	return *d2 - *d1;
}

static int cmp_string(const void *data1, const void *data2)
{
	char **d1 = (char **)data1;
	char **d2 = (char **)data2;

	return strcmp(*d1, *d2);
}

void bubble_sort(void *arr, int n, int size, cmp_t cmp)
{
	int i, j;
	void *ptr = malloc(size);

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++)	{
			if (cmp((char *)arr + j * size, (char *)arr + (j + 1) * size) > 0 ) {
				// 交换下标j 和下标j+1
				memcpy(ptr, (char *)arr + j * size, size);	
				memcpy((char *)arr + j * size, (char *)arr + (j + 1) * size, size);
				memcpy((char *)arr + (j + 1) * size, ptr, size);
			}
		}
	}

	free(ptr);
	ptr = NULL;
}

