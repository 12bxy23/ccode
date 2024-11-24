#include <stdio.h>

// 声明
char change(char c);

int main(void)
{
	char ch;
	char del;

	while (1) {
		printf("输入字符:");
		// scanf("%c", &ch);
		ch = getchar();
		// 吸收输入的'\n'
		// scanf("%c", &del);
		if (getchar() == '\n')
			;

		// 调用
		printf("转换后:%c\n", change(ch));
	}

	return 0;
}

/*
 字符大小写转换
 */
char change(char c)
{
	char res;

	if (c >= 'A' && c <= 'Z')
		res = c + ('a' - 'A');
	else if (c >= 'a' && c <= 'z')
		res = c - ('a' - 'A');

	return res;
}

