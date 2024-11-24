#include <stdio.h>
#include <string.h>

int main(void)
{
	size_t (*p)(const char *);
	int (*q)(const char *, const char *) = strcmp;

	p = strlen;

	printf("%ld\n", p("hello world"));
	printf("%d\n", q("hello", "hello"));

	return 0;
}

