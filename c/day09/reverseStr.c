#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int reverse_string(const char *ptr, char **r);
int main(void)
{
	char *s = NULL;

	reverse_string("good afternoon", &s); // char c; &c

	puts(s);

	free(s);
	s = NULL;

	return 0;
}

int reverse_string(const char *ptr, char **r) // char *p;
{
	int i, j;

	i = strlen(ptr);

	*r = malloc(i + 1);
	if (NULL == *r)
		return -1;

	for (i--, j = 0; i >= 0; i--, j++) {
		(*r)[j] = ptr[i];	
	}
	(*r)[j] = '\0';

	return 0;
}

