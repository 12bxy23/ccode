#include <stdio.h>

int c = 100;

// 外部声明
extern int add(int a, int b);

int main(void)
{
	printf("%d\n", add(1, 2));

	return 0;
}

