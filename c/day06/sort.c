#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N	10

int main(void)
{
	int a[N] = {};
	int i, j;
	int t;
	int max;

	srand(time(NULL));

	for (i = 0; i < N; i++) {
		a[i] = rand() % 100;
		printf("%d ", a[i]);	
	}
	printf("\n");

	// 冒泡排序
	for (i = 0; i < N - 1; i++) {
		// i就是第几趟
		for (j = 0; j < N - i - 1; j++) {
			// 相邻元素	
			if (a[j] > a[j+1]) {
				// 不符合大小关系则交换
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;	
			}
		}	
	}

	// 遍历
	printf("***************冒泡排序（从小到大）*************\n");
	for (i = 0; i < N; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	// 选择排序(从大到小)
	for (i = 0; i < N - 1; i++) {
		// i就是选择的位置
		max = i; // 假定所选择的位置对应的数值就是最大值
		for (j = i + 1; j < N; j++) {
			if (a[max] < a[j])
				max = j;
		}
		if (i != max) {
			// 假定的最大值不成立
			t = a[i];
			a[i] = a[max];
			a[max] = t;
		}
	
	}


	// 遍历
	printf("***************选择排序（从大到小）*************\n");
	for (i = 0; i < N; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	// 直接插入排序 从小到大
	for (i = 1; i < N; i++) {
		// i待插入到有序序列的元素的下标值
		t = a[i]; // t将待插入的元素备份
		for (j = i - 1; j >= 0; j--) {
			if (a[j] > t) {
				a[j + 1] = a[j];
			} else
				break;
		}
		a[j + 1]= t;
	}
	// 遍历
	printf("***************直接插入排序（从大到小）*************\n");
	for (i = 0; i < N; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}

