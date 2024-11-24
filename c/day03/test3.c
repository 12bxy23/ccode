/*
 10：定义两个整数a、b，a、b的取值范围在0-9之间，给出所有符合a+b=12的组合。
 */
#include <stdio.h>

int main(void)
{
	int a, b;

	for (a = 0; a < 10; a++) {
		for (b = 0; b < 10; b ++) {
			if (a + b == 12) {
				printf("%d + %d = 12\n", a, b);
			}
		}
	}

	return 0;
}

