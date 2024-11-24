#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD(a, b) ((a) + (b))
#define SUB(a, b) ((a) - (b))
#define MUL(a, b) ((a) * (b))
#define DIV(a, b) ((a) / (b))

int main(int argc, char **argv)
{
	int num1, num2;
	int ret;

	if (argc < 4)
		return 1;
	num1 = atoi(argv[1]);
	num2 = atoi(argv[3]);

	if (strcmp(argv[2], "+") == 0)
		ret = ADD(num1, num2);
	else if (strcmp(argv[2], "-") == 0)
		ret = SUB(num1, num2);
	else if (strcmp(argv[2], "x") == 0)
		ret = MUL(num1, num2);
	else if (strcmp(argv[2], "/") == 0)
		ret = DIV(num1, num2);

	printf("%d %s %d = %d\n", num1, argv[2], num2, ret);

	return 0;
}

