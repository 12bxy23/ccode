#include <stdio.h>

typedef union {
	char a;
	int b;
	long c;
	short d;
}u_t;

union un {
	char c;
	int n;
};

int main(void)
{
	u_t n;
	union un num;
	int number = 0x12345678;
	char *p = (char *)&number;

	printf("%x\n", *p);

	// 小端存储
	num.n = 0x12345678;
	printf("%x\n", num.c);

	printf("%ld\n", sizeof(n));

	return 0;
}


