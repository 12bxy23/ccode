#include <stdio.h>

#define N	10

int main(void)
{
	int a[N][N] = {};
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j <= i; j++) {
			if (0 == j || i == j)
				a[i][j] = 1;
			else {
				a[i][j] = a[i-1][j] + a[i-1][j-1];	
			}
			printf("%2d ", a[i][j]);
		}
		printf("\n");
	}

	return 0;
}

