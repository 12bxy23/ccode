#include <stdio.h>

int main(void)
{
	int i, j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 5; j++) {
			printf("i:%d, j:%d ", i, j);
		}
		printf("\n");
	}

	return 0;
}
	
