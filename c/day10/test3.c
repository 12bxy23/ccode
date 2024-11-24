#include <stdio.h>
#include <string.h>

void show_arr(const void *arr, int n, int size, void (*p)(const void *data));

void pri_char(const void *data)
{
	 const char *q = (const char *)data;
	 printf("%c", *q);
}

void pri_int(const void *data)
{
	const int *d = (const int *)data;
	printf("%d", *d);
}

void pri_string(const void *data)
{
	char **d = (char **)data;
	printf("%s ", *d);
}

int main(void)
{
	char s[] = "hello world";
	int a[] = {3,2,1,6,8,7,9,3,4};
	char *str[] = {"水煮牛肉", "小龙虾", "皮皮虾", "盒饭"};

	show_arr(s, strlen(s), sizeof(char), pri_char);
	printf("\n");
	show_arr(a, sizeof(a) / sizeof(int), sizeof(int), pri_int);
	printf("\n");
	show_arr(str, sizeof(str) / sizeof(char *), sizeof(char *), pri_string);
	printf("\n");

	return 0;
}

/*
   遍历任意类型的数组
arr:数组的起始地址
n:数组的成员个数
size:每个成员的字节个数
p:根据元素的地址，打印成员的函数
 */
void show_arr(const void *arr, int n, int size, void (*p)(const void *data))
{
	int i;

	for (i = 0; i < n; i++) {
		// arr[i]不成立 void*没有运算能力
		// (char *)arr + i * size 每个元素的地址
		p((char *)arr + i * size);
	}
}


