#include <stdio.h>
#include <stdlib.h> /*srand rand*/
#include <time.h> /*time()*/

/*
	随机产生10个偶数，将最大值，最小值输出 
	升级:
		要求产生的是质数
		所谓质数就是除了1和本身之外不能被其他数整除的数
 */
int main(void)
{
	int i, j;
	int num;
	int max, min;

	srand(time(NULL));	

	i = 0;
	while (i < 10) {
		num = rand() % 100;		
#if 0
		if (num % 2) {
			// 奇数
			continue; // 终止本次循环继续下一次循环
		}
		// 偶数
#endif
		// 判断生成的num是否为质数
		if (num == 1 || num == 0)
			continue; // 0 1都不是质数
		for (j = 2; j < num; j++) {
			if (num % j == 0) {
				// 除了1和本身，遇到了能整除的数
				break; // 终止for循环
			}
		}
		if (j < num) {
			// 说明循环条件是成立的，由于num % j == 0而break终止的循环,也就是除了1和本身之外有被num整除的数为j
			continue;
		}
		// 是质数
		printf("%d ", num);
		if (i == 0) {
			// 第一个偶数
			min = max = num; // 赋值运算符是可以连续赋值的，自右向左
		} else {
			// 不是第一个了，那么你认为的最大最小值成立吗
			if (max < num)
				max = num;
			if (min > num)
				min = num;
		}

		i ++;
	}
	printf("\n");

	printf("max:%d, min:%d\n", max, min);

	return 0;
}

