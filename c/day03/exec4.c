#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 计时器

int main(void)
{
	int h, m, s;

	for (h = 0; h < 24; h ++) {
		for (m = 0; m < 60; m ++) {
			for (s = 0; s < 60; s ++) {
				system("clear");
				printf("%02d:%02d:%02d\n", h, m, s);
				sleep(1);
			}
		}
	}

	return 0;
}

