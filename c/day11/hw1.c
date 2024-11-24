#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int ret;
	char *p = NULL;;
	int i;

	if (argc < 3)	
		return 1;

	ret = strcmp(argv[1], argv[2]);
	if (ret > 0) {
		p = argv[1];	
	} else
		p = argv[2];

	for (i = strlen(p) - 1; i >= 0; i--) {
		putchar(p[i]);
	}	
	putchar('\n');

	return 0;
}

