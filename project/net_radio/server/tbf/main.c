#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "tbf.h"

#define BUFSIZE	32
#define CPS		10

int main(int argc, char *argv[]/*char **argv*/)
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt;
	int td;
	int n;

	if (argc < 2)
		return 1;

	// 初始化令牌桶
	td = tbf_init(CPS, CPS*10);
	if (-1 == td)
		return 1;

	// 打开
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd) {
		return -1;		
	}

	// cat
	while (1) {
		// 取令牌
		n = tbf_fetch_token(td, CPS);

		// 重复使用buf，建议buf清理干净，防止有脏数据	
		memset(buf, 0, BUFSIZE);
		cnt = read(fd, buf, n);
		if (0 == cnt) {
			// 读完了
			break;
		} else if (-1 == cnt) {
			// 出错了
			goto ERROR;
		}
		// 成功了
		write(1, buf, cnt); // 注意读多少写多少
	}

	tbf_destroy(td);

	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}


