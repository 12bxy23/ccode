#include <stdio.h>

int myatoi(const char *p);

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	// argv[1]转换为整型 
	// ./a.out "123"  --->123
	// '1'--->1 ('1' - '0')
	printf("%d\n", myatoi(argv[1]));

	return 0;
}

int myatoi(const char *p)
{
	int ret = 0;

	while (*p) {
		ret = ret * 10 + (*p - '0');
		p++;
	}

	return ret;
}


