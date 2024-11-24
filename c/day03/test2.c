/*
 输出小写的a-z以及大写的在Z—A
 */
#include <stdio.h>

int main(void)
{
	int i;

	for (i = 0; i < 26; i++) {
		printf("%c ", 'a' + i);
		printf("%c ", 'Z' - i);
	}
	printf("\n");

	return 0;
}

