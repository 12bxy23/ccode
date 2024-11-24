#include <stdio.h>

typedef struct stu_st{
	int age;
	// 结构体类型的指针
	// stu_t *prev, *next; 错误的
	struct stu_st *prev, *next; // 允许的
}stu_t;

int main(void)
{
	stu_t a, b, c;

	a.age = 1;
	a.next = &b;
	a.prev = &c;

	b.age = 2;
	c.age = 3;

	printf("%d\n", (a.prev)->age); // c.age
	printf("%d\n", (a.next)->age); // b.age


	return 0;
}

