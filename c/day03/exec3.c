/*
 A
 A B
 A B C
 A B C D
 */
#include <stdio.h>

int main(void)
{
	int i, j;
	int line;

	printf("line:");
	scanf("%d", &line);

	for (i = 0; i < line; i++) {
		// for (j = 0; j <= i; j ++) {
		for (j = i; j >= 0; j --) { // 倒序
			// 注意不要轻易改变j的值，会影响循环条件
			printf("%c ", 'A' + j % 26);
		}
		printf("\n");
	}

	return 0;
}

