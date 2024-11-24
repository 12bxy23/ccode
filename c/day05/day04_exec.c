#include <stdio.h>

int is_lower(char c);
int is_upper(char c);
int is_alph(char c);
char change(char c);

int main(void)
{
	char ch;
	int i;

	i = 0; 
	while (i < 20) {
		scanf("%c", &ch);
		if (!is_alph(ch))
			printf("%c", ch);
		else {
			printf("%c", change(ch));
		}
		i++;
	}

	return 0;
}

// 是否为字母
int is_alph(char c)
{
	return is_upper(c) || is_lower(c);
}

int is_upper(char c)
{
	return c >= 'A' && c <= 'Z';
}

int is_lower(char c)
{
	return c >= 'a' && c <= 'z';
}

char change(char c)
{
	if (is_upper(c))
		return c + ('a' - 'A');
	else if (is_lower(c))
		return c - ('a' - 'A');
	else
		return -1;
}

