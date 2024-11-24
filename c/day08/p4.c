#include <stdio.h>

int main(void)
{
	char s[] = "hello";
	// 常量指针
	// const char *p = s;
	char const *p = s;
	// 指针常量
	char *const q = s;

	// *p = 'w';
	*q = 'w';
	q ++;

	puts(s); // 输出整个字符串

	return 0;
}


