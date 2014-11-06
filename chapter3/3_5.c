/*****************
  对于指定的描述符打印文件标志
  *****************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

int main(int argc, char **argv)
{
	int		val;
	if (argc != 2){
		perror("usage:a.out <descriptor#>");
		return 1;
	}

	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0){
		printf("fcntl error for %d\n", atoi(argv[1]));
		return 1;
	}

	switch (val & O_ACCMODE){
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			perror("unknown access mode");
			break;
	}

	if (val & O_APPEND){
		printf(", append");
	}
	if (val & O_NONBLOCK){
		printf(", noblocking");
	}
#if defined(O_SYNC)
	if (val & O_SYNC)
		printf(", synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
	if (val & O_FSYNC)
		printf(",synchronous writes");
#endif
	putchar('\n');

	return 0;
}
