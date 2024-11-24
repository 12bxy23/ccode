#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int *p;

	p = malloc(100);
	// 将所开辟的存储空间初始化为0
	// memset(p, 0, 100);
	bzero(p, 100);

	return 0;
}

