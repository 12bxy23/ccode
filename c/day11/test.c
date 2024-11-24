#include <stdio.h>
#include <string.h>

/*
	定义类型，一般全局定义
 */
#define NAMESIZE	32
#define N			2

struct stu_st {
	int age;
	char name[NAMESIZE];
	float score;
};

int main(void)
{
	struct stu_st arr[N];
	int i;
	int max = 0;

	for (i = 0; i < N; i++) {
		scanf("%d%s%f", &arr[i].age, arr[i].name, &arr[i].score);
		if (i != 0) {
			// max = 0
			if (arr[i].score > arr[max].score)
				max = i;
		}
	}
	printf("最高成绩:%s %d %f\n", arr[max].name, arr[max].age, arr[max].score);

	return 0;
}

