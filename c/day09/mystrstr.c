#include <stdio.h>

char *mystrstr(const char *s1, const char *s2);
int main(void)
{
	char *p1 = "good mmmmmorning";
	char *p2 = "morn";
	char *ret;

	ret = mystrstr(p1, p2);
	if (NULL == ret)
		printf("没有\n");
	else
		printf("找到了，第一次出现子串的位置:%s\n", ret);

	return 0;
}

char *mystrstr(const char *s1, const char *s2)
{
	const char *s1_p, *s2_p;

	while (*s1) {
		if (*s1 == *s2) {
			s1_p = s1 + 1;
			s2_p = s2 + 1;
			while (*s1_p == *s2_p && *s2_p) {
				s1_p++;		
				s2_p++;		
			}
			if (*s2_p == '\0')	
				return (char *)s1;
		}
		s1++;
	}

	return NULL;
}

