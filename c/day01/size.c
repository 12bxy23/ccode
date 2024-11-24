#include <stdio.h>

int main(void)
{
	/*
	 	sizeof运算符
		sizeof(变量名/类型)计算这个变量或者类型所占的存储空间大小
	 */
	printf("char:%ld\n", sizeof(char));
	printf("short:%ld\n", sizeof(short));
	printf("int:%ld\n", sizeof(int));
	printf("long:%ld\n", sizeof(long));
	printf("long long:%ld\n", sizeof(long long));

	printf("float:%ld\n", sizeof(float));
	printf("double:%ld\n", sizeof(double));
	printf("long double:%ld\n", sizeof(long double));

	return 0;
}

