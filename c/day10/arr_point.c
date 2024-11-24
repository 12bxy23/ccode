#include <stdio.h>

int main(void)
{
	int arr[10] = {};
	// a数组首元素的地址，a===>&a[0]  a[0]是一个数组，数组中有3个int类型的变量，所以&a[0]就是这三个整型变量的地址
	int a[2][3] = {};
	int (*q)[3]= a;

	// int [10] *
	int (*p)[10]= &arr;

	printf("%ld\n", sizeof(p));
	printf("p:%p\n", p);
	printf("p + 1:%p\n", p + 1);

	// int *
	printf("arr:%p\n", arr);
	printf("arr + 1:%p\n", arr + 1);
	printf("&arr:%p\n", &arr);
	printf("&arr + 1:%p\n", &arr + 1);

	return 0;
}

