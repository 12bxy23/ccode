#include <stdio.h>

/*
 04：写一个方法，此方法实现输出100-999之间的水仙花数。
 */

int main(void)
{
	int i;
	int sum = 0; // 立方和
	int save;
	int n;

	for (i = 100; i < 1000; i++) {
		// 判断i是否为水仙花
		save = i;
		sum = 0; // !!!!初始化
		while (save) {
			n = save % 10;
			sum += n * n * n; // 最低位的立方和
			save /= 10;
		}
		// 立方和是否根这个数相等
		if (sum == i)
			printf("%d是一个水仙花数\n", i);			
	}

	return 0;
}

