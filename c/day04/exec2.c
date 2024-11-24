#include <stdio.h>

int is_symmetry(int num);

int main(void)
{
	int n;

	printf("输入一个整型数:");
	scanf("%d", &n);

	if (is_symmetry(n)) {
		printf("%d是一个对称数\n", n);
	} else
		printf("%d不是一个对称数\n", n);

	return 0;
}

// 判断是否为对称数
int is_symmetry(int num)
{
	int reverse_num = 0;
	int save;

	// 将num到序数求出
	save = num;
	while (save) {
		reverse_num = reverse_num * 10 + save % 10;	
		save /= 10;
	}

	return reverse_num == num;
}


