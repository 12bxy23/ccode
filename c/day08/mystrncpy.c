#include <stdio.h>

#define N	10

char *mystrncpy(char *dest, const char *src, size_t n);

int main(void)
{
	char d[N] = {};	
	char *p = "hello world";

	mystrncpy(d, p, 9);
	puts(d);

	return 0;
}

char *mystrncpy(char *dest, const char *src, size_t n)
{
	int i;

	for (i = 0; src[i] && i < n; i++) {
		dest[i] = src[i];
	}
	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}

