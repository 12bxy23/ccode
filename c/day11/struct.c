#include <stdio.h>
#include <string.h>

/*
	定义类型，一般全局定义
 */
#define NAMESIZE	32

struct stu_st {
	int age;
	char name[NAMESIZE];
	float score;
};

int main(void)
{
	// 定义结构体类型的变量
	struct stu_st s1;
	// 初始化
	struct stu_st s2 = {21, "小黑", 90};
	struct stu_st *p;

	p = &s2;

	// 赋值
	s1.age = 20;
	strcpy(s1.name, "小白");
	s1.score = 100;

	// 访问
	printf("%d %s %f\n", s1.age, s1.name, s1.score);
	printf("%d %s %f\n", (&s1)->age, s1.name, s1.score);
	printf("%d %s %f\n", p->age, p->name, p->score);

	return 0;
}

