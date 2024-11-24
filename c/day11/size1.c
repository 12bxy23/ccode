#include <stdio.h>

typedef struct {
	char a;
	char b;
}s1_t;

typedef struct {
	char a;
	short b;
}s2_t;

typedef struct {
	char a; // 0
	int b;  // 4
	char c; // 8 整体最大成员的倍数
	char d; // 9
}s3_t;

typedef struct {
	char a;
	char c;
	short d;
	long b;
}s4_t;

typedef struct {
	char a;
	long double b; // 16
}s5_t;

typedef struct {
	char a;
	// s4_t m; // 结构体成员 16 按照结构体中最大成员对齐
	s5_t n;
}s6_t;

int main(void)
{
	s1_t s1;
	s2_t s2;
	s3_t s3;
	s4_t s4;
	s5_t s5;
	s6_t s6;

	printf("&s4.a:%p\n", &s4.a);
	printf("&s4.c:%p\n", &s4.c);
	printf("&s4.d:%p\n", &s4.d);
	printf("&s4.b:%p\n", &s4.b);

	printf("sizeof(s1):%ld\n", sizeof(s1));
	printf("sizeof(s2):%ld\n", sizeof(s2));
	printf("sizeof(s3):%ld\n", sizeof(s3));
	printf("sizeof(s4):%ld\n", sizeof(s4));
	printf("sizeof(s5):%ld\n", sizeof(s5));
	printf("sizeof(s6):%ld\n", sizeof(s6));

	return 0;
}

