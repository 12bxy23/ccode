#include <stdio.h>

#define N	128

char change(char c);
int is_upper(char c);
int is_lower(char c);

int main(void)
{
	char s[N] = {};
	int i;

	// 读入
	i = 0;
	do {
		scanf("%c", s + i);
		if (s[i] == '\n') {
			// 一行结束
			s[i] = '\0';
			break;
		}
		i++;
	} while (i < N);
	if (i == N - 1)
		s[i] = '\0';

	// 大小写转化
	for (i = 0; s[i]; i++) {
		if (!(is_upper(s[i]) || is_lower(s[i])))
			printf("%c", s[i]);
		printf("%c", change(s[i]));	
	}
		
	printf("\n");

	return 0;
}

int is_upper(char c)
{
	return c  >= 'A' && c <= 'Z';
}

int is_lower(char c)
{
	return c >= 'a' && c <= 'z';
}

char change(char c)
{
	if (is_upper(c))
		return c + ('a' - 'A');
	if (is_lower(c))
		return c - ('a' - 'A');
}


