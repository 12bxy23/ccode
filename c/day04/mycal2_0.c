#include <stdio.h>

// 1970.1.1 星期四

// 声明
int isleap(int y);
int month_days(int m, int y);

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
		// 函数的调用,传参的时候是值传递
		sumdays += isleap(i) ? 366 : 365;
	}
	for (i = 1; i < month; i++) {
		// 函数的调用
		sumdays += month_days(i, year);
	}

	sumdays += 1; // year.month.1 1号这一天

	// 由于1970.1.1不是星期一 而是星期四
	weekday = (sumdays + 3) % 7;

	// 求year.month有多少天
	monthdays = month_days(month, year);

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

/*
 判度平年闰年
 需要知道你要判断的是哪一年，所以需要参数
 是闰年返回1 不是返回0
 */
int isleap(int y)
{
	// return语句用于函数的返回值
	return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}

/*
 计算月份的天数
 需要知道你要计算的是哪月，如果是2月还需要知道是哪年的二月(参数)
 返回值就是天数
 */
int month_days(int m, int y)
{
	int mdays;

	if (1 == m || 3 == m || 5 == m || 7 == m || 8 == m || 10 == m || 12 == m)
		mdays = 31;
	else if (4 == m || 6 == m || 9 == m || 11 == m)
		mdays = 30;
	else
		mdays = isleap(y) + 28;

	return mdays; // 注意返回的是值，不是变量
}






