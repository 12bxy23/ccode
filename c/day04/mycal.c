#include <stdio.h>

// 1970.1.1 星期四

int main(void)
{
	int year, month;
	int sumdays = 0;
	int i;
	int weekday;
	int monthdays;

	do {
		printf("请输入日期(year month):");
		scanf("%d%d", &year, &month);
	} while (!(year >= 1970 && month >= 1 && month <= 12));

	// year.month.1是星期几--->year.month.1 ~ 1970.1.1有多少天
	for (i = 1970; i < year; i++) {
		sumdays += ((i % 4 == 0 && i % 100 != 0 || i % 400 == 0) ? 366 : 365);
	}
	for (i = 1; i < month; i++) {
		if (1 == i || 3 == i || 5 == i || 7 == i || 8 == i || 10 == i || 12 == i)
			sumdays += 31;
		else if (4 == i || 6 == i || 9 == i || 11 == i)
			sumdays += 30;
		else
			sumdays += (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) + 28;
	}

	sumdays += 1; // year.month.1 1号这一天

	// 由于1970.1.1不是星期一 而是星期四
	weekday = (sumdays + 3) % 7;

	if (1 == month || 3 == month || 5 == month || 7 == month || 8 == month || 10 == month || 12 == month)
		monthdays = 31;
	else if (4 == month || 6 == month || 9 == month || 11 == month)
		monthdays = 30;
	else
		monthdays = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) + 28;

	// 日历的打印
	printf("       %d月%d\n", month, year);
	printf("日 一 二 三 四 五 六\n"); // 一个中文占两个字符宽度
	for (i = 0; i < weekday; i++)
		printf("   ");
	for (i = 1; i <= monthdays; i++) {
		printf("%2d%c", i, (i + weekday) % 7 == 0 ? '\n' :' ');
	}
	printf("\n");

	return 0;
}

