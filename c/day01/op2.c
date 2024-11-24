#include <stdio.h>

int main(void)
{
	int m, n;

	scanf("%d%d", &m, &n);

	// m大于0的同时n小于100
	printf("%d\n", m > 0 && n < 100);
	printf("%d\n", m > 0 && n++);
	printf("n:%d\n", n);

	printf("%d\n", m > 0 || n < 100);
	printf("%d\n", !(m > 0 || n++));
	printf("n:%d\n", n);

	// 赋值
	m = 100; // m等于100 m == 100

	m += 100; //m = m + 100

	// ?:
	printf("%s\n", m % 2 == 0 ? "偶数" : "奇数");

	// ,
	m = 1, n = 2;
	m = (n++, m++, m+n);
	printf("m:%d, n:%d\n", m, n);

	return 0;
}

