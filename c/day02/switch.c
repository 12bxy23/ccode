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

	// switch
	switch (score / 10) {
		case 10:
			printf("满分通过\n");
		case 9:
			level = 'A';
			break; // 结束分支
		case 8:
			level = 'B';
			break;
		case 7:
			level = 'C';
			break;
		case 6:
			level = 'D';
			break;
		default:
			level = 'E';
			break;
	}

	printf("你的成绩所属等级为%c\n", level);

	return 0;
}

