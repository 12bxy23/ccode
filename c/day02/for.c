#include <stdio.h>

/*
 求100的前n项和
 升级：
 	将100内所有能同时被4和6整除的数累加起来
 在升级:
 	累加之和不要超过400
 */

int main(void)
{
	// 在函数内定义的变量如果未初始化值是随机值，对需要直接参与运算的变量必须初始化
	int sum = 0; // 累加器	
	int i;
#if 0	
	sum += 1;
	sum += 2;
	....
	sum += 100;
#endif
	// 使用循环变量i来取得100内的每一个数值
	for (i = 1; i <= 100; i++) {
		if (i % 4 == 0 && i % 6 == 0) {
			sum += i;
			if (sum > 400) {
				sum -= i;
				break; // 超过400则减掉并终止循环
			}
		}
	}
	
	printf("100的前n项和为:%d\n", sum);

	return 0;
}

