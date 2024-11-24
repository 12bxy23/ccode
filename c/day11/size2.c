#include <stdio.h>

typedef struct {
	short a;
	long b;
}t;

typedef struct {
	char a; //0~1
	int b[3]; // 4~16
	t c; // 8的倍数 16~32
	char *d; // 32~40
}s_t;

int main(void)
{
	s_t test;

	printf("%ld\n", sizeof(test));

	return 0;
}

