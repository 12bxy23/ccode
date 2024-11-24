#include <stdio.h>
#include <string.h>

#define N	128	

int main(void)
{
	char s[] = "hilo world";
	int i, j;
	char dest[N] = "hello world";
	int ret;

	// 字符串的比较 两个字符串依次比较每一个字符的ascii值，从第一个不相等的ascii开始，ascii大的字符串就大 "hello", "hi"
	printf("%d\n", strcmp(s, dest));
	// 比较s数组中的字符串和dest数组中的字符串的大小，得到的大小值就是第一个不相等的字符的ascii差值
	for (i = 0; s[i] == dest[i] && s[i]; i++) {
		;
	}
	ret = s[i] - dest[i];
	printf("ret:%d\n", ret);

#if 0
	// 字符串的拼接
	printf("%s\n", strcat(dest, s));
	// 尝试实现
	for (i = strlen(dest), j = 0; s[j]; i++, j++)	
		dest[i] = s[j];
	dest[i] = '\0';
	printf("%s\n", dest);
#endif

#if 0
	printf("%ld\n", strlen(s));
	// 尝试实现strlen，暂且在main中实现

	for (i = 0; s[i]; i++)
		;
	printf("长度:%d\n", i);
#endif
#if 0
	// 字符串的复制
	strcpy(dest, s);
	printf("dest:%s\n", dest);
	strcpy(dest, "easthome");
	printf("dest:%s\n", dest);
	// 尝试实现

	for (i = 0; s[i]; i++)
		dest[i] = s[i];
	// dest数组中有\0?
	dest[i] = '\0';
	printf("dest:%s\n", dest);
#endif

	return 0;
}

