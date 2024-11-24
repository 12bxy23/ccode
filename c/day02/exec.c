#include <stdio.h>

int main(void)
{
	int x, y, z;
	int t; // 中间变量

	printf("输入三个整型数:");
	scanf("%d%d%d", &x, &y, &z);

	// 从大到小输出
	if (x < y) {
		// ^异或
#if 0
		t = x;
		x = y;
		y = t;	
#endif
		// 一个整型数^本身结果是0  一个整型数^0结果是自身
		x = x ^ y;
		y = x ^ y;
		x = x ^ y;
	}
	if (x < z) {
		t = x;
		x = z;
		z = t;
	}
	if (y < z) {
		t = y;
		y = z;
		z = t;
	}

	printf("从大到小:%d %d %d\n", x, y, z);

	return 0;
}

