#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 while
	来一个猜数字游戏
	请猜测100以内的一个数,游戏有三次机会。这个数由系统随机产生
 随机数的产生
 	rand() 可以产生一个0~65535之间的一个随机数 如果使用这个接口需要包含头文件stdlib.h
	rand()程序每次执行产生的一些列随机数不变
	需要使用srand()提供随机数算法的种子，只要种子不同，随机数就不同
	srand(time(NULL))
	time()需要time.h头文件
 */

int main(void)
{
	int num;
	int guess;
	int times = 0;

	// 提供种子	
	srand(time(NULL));

	num = rand() % 10;
	while (times < 3) {
		// 合理性校验
		do {
			printf("猜(10以内):");	
			scanf("%d", &guess);
		} while ((guess >= 10 || guess < 0) && printf("再来一次,")); // printf返回值是输出的成员个数
		if (guess == num) {
			printf("猜中了!!!!!\n");
			break; // 结束循环
		} else {
			if (guess > num)
				printf("大了\n");
			else
				printf("小了\n");
			printf("很遗憾！别放弃！\n");
			times++;
		}
	}
	if (times == 3)
		printf("今天运气差点意思!明天再来\n");

	return 0;
}

