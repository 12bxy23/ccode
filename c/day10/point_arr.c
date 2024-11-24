#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// main是谁调用的？内核代码调用
int main(int argc, char *argv[] /*char **argv*/)
{
	char *p = "hello"; // p仅仅存储的是"hello"首地址
	char *arr[] = {"麻辣烫", "米线", "红烧肉", "炸鸡", "烧烤", "烤鸭", "盖饭", "盒饭"};
	int i;

	srand(time(NULL));

	i = rand() % (sizeof(arr) / sizeof(char *));
	printf("今天中午吃:%s\n", arr[i]);

	for (i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	return 0;
}

