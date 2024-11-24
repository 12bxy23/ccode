#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int add_element(int **p, int *n, int elm);
void show_arr(const int *arr, int n);
int del_element(int **p, int *n, int key);

int main(void)
{
	int *arr = NULL;
	int num = 0;
	int i = 0;

	for (i = 0; i < 10; i++) {
		add_element(&arr, &num, i);
	}
	show_arr(arr, num);

	del_element(&arr, &num, 4);
	del_element(&arr, &num, 8);
	show_arr(arr, num);

	return 0;
}

// 增加新元素
int add_element(int **p, int *n, int elm)
{
	*p = realloc(*p, (*n + 1) * sizeof(int));
	if (NULL == *p)
		return -1;
	(*p)[*n] = elm;
	(*n) ++;

	return 0;
}

// 遍历数组
void show_arr(const int *arr, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/*
 查找指定元素的位置
 */
static int __find(const int *arr, int n, int key)
{
	int i;

	for (i = 0; i < n; i++)
		if (arr[i] == key)
			return i;
	return -1;
}

int del_element(int **p, int *n, int key)
{
	int i;
	// 先找再删除	
	int f = __find(*p, *n, key);
	if (-1 == f)
		return -1;
	// 下标为f的元素就是要删除的元素
#if 0
	for (i = f+1; i < *n; i++)
		(*p)[i-1] = (*p)[i];
#endif
	// *p是int * 运算能力sizeof(int)
	memcpy((*p) + f, (*p) + f + 1, (*n - (f + 1)) * sizeof(int));
	(*n)--;
	*p = realloc(*p, *n * sizeof(int));
	if (NULL == *p)
		return -1;
	return 0;
}

