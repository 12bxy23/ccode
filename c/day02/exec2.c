#include <stdio.h>

int main(void)
{
	int num;
	int sign = 1; // 符号标记
	int res;

	printf("number:");
	scanf("%d", &num);

	if (num < 0) {
		sign = -1;
		num = -num;
	}

	// 都是正数
	res = 0;
	while (num > 0) {
		res = res * 10 + num % 10;	
		num /= 10; // num = num / 10;
	}

	printf("倒序数:%d\n", res * sign);

	return 0;
}

