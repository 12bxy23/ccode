#include <stdio.h>

// LEFT默认就是0 一次递增 LEFT RIGHT UP DOWN都是常量
enum {LEFT, RIGHT, UP, DOWN, QUIT = 9, TEST};
// TEST就是10

int main(void)
{
	int direction;

	while (1) {
		scanf("%d", &direction);

		switch (direction) {
			case LEFT:
				printf("左移\n");
				break;
			case RIGHT:
				printf("右移\n");
				break;
			case UP:
				printf("图形变换\n");
				break;
			case DOWN:
				printf("加速\n");
				break;
			case QUIT:
				goto GAMEOVER; // 无条件跳转到标号位置
			default:
				printf("这是什么操作\n");
				break;
		}
	}
	
GAMEOVER: // 标号
	printf("游戏结束\n");
	return 0;
}

