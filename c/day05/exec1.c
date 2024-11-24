#include <stdio.h>

/*
 最大公约数
 */
int is_common_divisor(int m, int n);

int main(void)
{
	int num1, num2;

	scanf("%d%d", &num1, &num2);

	printf("%d和%d的最大公约数是%d\n", num1, num2, \
			is_common_divisor(num1, num2));

	return 0;
}

int is_common_divisor(int m, int n)
{
	int i;

	if (m < n) {
		m = m ^ n;
		n = m ^ n;
		m = m ^ n;
	}
	// m一定是两个数中大的， n是小的
	
	for (i = n; i > 0; i--) {
		if (m % i == 0 && n % i == 0)
			break;
	}

	return i;
}



