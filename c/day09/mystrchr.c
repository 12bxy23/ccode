#include <stdio.h>

char *mystrchr(const char *ptr, int c);
int main(void)
{
	char c = 'e';
	char *p = "hello world";
	char *ret;

	ret = mystrchr(p, c);
	if (NULL == ret)
		printf("没有要找的字符\n");
	else
		puts(ret);

	return 0;
}

char *mystrchr(const char *ptr, int c)
{
	while (*ptr) {
		if (*ptr == c)
			return (char *)ptr;
		ptr++;
	}

	return NULL;
}


