/*
 读入一个学生的成绩，判断这个学生的成绩属于哪个等级
 90~100 A
 80~89  B
 70~79  C
 60~69  D
 0~59   E

 分析:
 	读入学生的成绩scanf
	由于登记有5个，多个条件，得知需要使用else if 
 */
#include <stdio.h>

int main(void)
{
	int score;
	char level;

	printf("输入你的成绩:");
	scanf("%d", &score);

	if (score >= 90 && score <= 100) {
		level = 'A';	
	} else if (score >= 80 && score < 90) {
		level = 'B';
	} else if (score >= 70 && score < 80) {
		level = 'C';
	} else if (score >= 60 && score < 70) {
		level = 'D';
	} else {
		level = 'E';
	}

	printf("你的成绩所属等级为%c\n", level);

	return 0;
}

