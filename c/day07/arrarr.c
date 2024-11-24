#include <stdio.h>

int main(void)
{
	int a[2][3] = {1,2,3,4,5,6};
	int i, j;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d %d %d ", a[i][j], *(a[i] + j), *(*(a + i) + j));
		}
		printf("\n");
	}

	// a是数组的地址
	printf("a:%p\n", a);
	printf("a + 1:%p\n", a + 1);

	// 对数组的地址取值就得到了元素的地址
	printf("a[0]:%p\n", a[0]);
	printf("a[0] + 1:%p\n", a[0] + 1);

	// 对元素的地址取值就得到了元素
	printf("a[0][0]:%d\n", a[0][0]);
	printf("*a[0]:%d\n", *a[0]);

	return 0;
}
