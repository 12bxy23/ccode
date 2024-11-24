#include <stdio.h>

// 定义新类型
typedef int num_t; // num_t由整型变量提升为整型
// c语言中有很多typedef类型，例如size_t就是long ssize_t

int main(void)
{
	num_t n; // n就是整型变量
	size_t s;

	printf("sizeof(s):%ld\n", sizeof(s));
	printf("sizeof(ssize_t):%ld\n", sizeof(ssize_t));

	return 0;
}

