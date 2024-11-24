#include <stdio.h>

int main(void)
{
	// 定义一个由10个int类型变量组成的数组，数组中的值是随机值
	int a1[10];
	int a2[3] = {1, 2, 3};
	int a3[] = {1, 2, 3, 4, 5, 6, 7};
	int i;

	// a1数组中的每一个元素赋值
	for (i = 0; i < 10; i++) {
		a1[i] = i + 1; // 赋值
		printf("%d ", a1[i]); // 取得值
	}
	printf("\n");

	// 访问每一个元素的地址
	for (i = 0; i < 10; i++) {
		printf("%p\n", &a1[i]);
	}
	// 数组名
	printf("%p\n", a1);
	// a1 ++;

	// 整个数组中所有元素所占存储空间的总大小
	printf("%ld\n", sizeof(a1));

	// 数组的成员个数
	printf("%ld\n", sizeof(a1) / sizeof(int));

	return 0;
}

