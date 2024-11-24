#include <stdio.h>

int main(void)
{
	int n; // 定义一个整型变量

	printf("请输入:");
	scanf("%d", &n); // 不要忘记取地址, 注意参数间,后的空格

	printf("得到n:%d\n", n);

	return 0;
}

