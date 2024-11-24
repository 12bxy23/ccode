#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div2num(int a, int b);

int op(int a, int b, int (*p)(int, int));

int main(int argc, char **argv)
{
	int num1, num2;
	int ret;

	if (argc < 4)
		return 1;
	num1 = atoi(argv[1]);
	num2 = atoi(argv[3]);

	if (strcmp(argv[2], "+") == 0)
		ret = op(num1, num2, add);
	else if (strcmp(argv[2], "-") == 0)
		ret = op(num1, num2, sub);
	else if (strcmp(argv[2], "x") == 0)
		ret = op(num1, num2, mul);
	else if (strcmp(argv[2], "/") == 0)
		ret = op(num1, num2, div2num);

	printf("%d %s %d = %d\n", num1, argv[2], num2, ret);

	return 0;
}

/*
 对于两个整型变量做任意的四则运算
 */
int op(int a, int b, int (*p)(int, int))
{
	return p(a, b);
}


int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div2num(int a, int b)
{
	return a / b;
}



