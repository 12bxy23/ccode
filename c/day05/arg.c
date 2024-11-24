#include <stdio.h>

void test(int a, int b, int c);
int main(void)
{
	volatile int n = 1;
	int n1, n2;

	n1 = 1, n2 = 2;

	test(n, n++, ++n);
	test(n1++, n2++, n1 + n2);

	return 0;
}

void test(int a, int b, int c)
{
	printf("a:%d, b:%d, c:%d\n", a, b, c);
}


