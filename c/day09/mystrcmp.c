#include <stdio.h>

int mystrcmp(const char *s1, const char *s2);

int main(void)
{
	printf("%d\n", mystrcmp("hello", "hello"));
	printf("%d\n", mystrcmp("ho", "hello"));
	printf("%d\n", mystrcmp("aho", "hello"));

	return 0;
}

int mystrcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1) {
		s1 ++;
		s2 ++;	
	}
	return *s1 - *s2;
}



