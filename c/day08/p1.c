#include <stdio.h>

size_t mystrlen(char *p);
void swap2num(int *m, int *n);

int main(void)
{
	char s[] = "hello";
	// char *类型 p是变量名 s赋值给p
	char *p = s;
	int a, b;

	a = 1, b = 2;	
	swap2num(&a, &b);
	printf("a:%d, b:%d\n", a, b);

#if 0
	printf("%c\n", *p);	
	printf("%c\n", p[0]);
	
	// p和s唯一的区别是p值变量 s是常量
	p++;
	printf("%c\n", *p);
	p++;
	p++;
	printf("%c\n", p[1]);
	printf("%c\n", s[1]);

	printf("长度:%ld\n", mystrlen(s));
#endif

	return 0;
}

// strlen 指针变量p存储的就是所要求长度的字符串的起始地址
size_t mystrlen(char *p)
{
	size_t len = 0;

	while (*p) {
		len ++;
		p++;
	}

	return len;
}

/*
 两个整型变量的交换
 行参改变实参
 */
void swap2num(int *m, int *n)
{
	int t;

	t = *m;
	*m = *n;
	*n = t;
}




