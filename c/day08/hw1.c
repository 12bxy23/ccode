#include <stdio.h>

int word_string(const char *p);

int main(void)
{
	char *str = "     he  llo     world  ";
	
	printf("单词的个数:%d\n", word_string(str));

	return 0;
}

// 统计单词的个数
int word_string(const char *p)
{
	int space_flag = 0;
	int word_cnt = 0;

	if (strcmp(p, "") == 0)
		return 0;

	// 将开头是空格的情况，跳过
	while (*p == ' ')
		p++;

	// *p一定不是空格
	while (*p) {
		if (*p == ' ') {
			space_flag++;
		} else {
			space_flag = 0;
		}
		if (space_flag == 1) {
			// 第一次遇到' '
			word_cnt++;
		}
		p++;
	}

	if (*(p-1) != ' ')
		word_cnt++;

	return word_cnt;
}

