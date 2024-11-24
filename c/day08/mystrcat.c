#include <stdio.h>
#include <string.h>

#define N	10

char *mystrncat(char *dest, const char *src, size_t n);

int main(void)
{
	char d[N] = "hi";	
	char *p = "hello world";

	mystrncat(d, p, 3);
	puts(d);

	return 0;
}

char *mystrncat(char *dest, const char *src, size_t n)
{
	int i;
	int len;

	len = strlen(dest);

	strncpy(dest + len, src, n);
	// 由于strncpy在src字符串长度大于n的时候没有复制'\0'
	// 而strncat一定在最后追加的'\0'
	if (strlen(src) > n) {
		dest[len + n] = '\0';
	}

	return dest;
}

