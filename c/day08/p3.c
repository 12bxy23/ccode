#include <stdio.h>

void show_arr(int *arr, int n);
int main(void)
{
	int arr[6] = {1, 7, 3, 6, 2, 9};
	int *p;

	p = arr;

	printf("%d\n", *p++); // *p p++
	show_arr(arr, 6);
	printf("%d\n", (*p)++); // *p (*p)++-->arr[1]++
	show_arr(arr, 6);
	printf("%d\n", *(p++)); // *p p++
	show_arr(arr, 6);
	printf("%d\n", ++*p); // *p-->arr[2] ++*p -->++arr[2]
	show_arr(arr, 6);
	printf("%d\n", *++p); // ++p *p
	show_arr(arr, 6);
		
	return 0;
}

void show_arr(int *arr, int n)
{
	int i;

	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}




