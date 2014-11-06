/*****************
  1. 如果没有lseek的SEEK_END,则在多进程读取数据的情况下，temp.foo中可能是大小写的输出混合。
  2. open可以通过设置O_APPEND选项来达到这种混乱，或者通过lseek来解决这种混乱
  ****************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int	fd1;
	int	fd2;
	pid_t	pid;
	char	buf1[] = "abcde";
	char	buf2[] = "ABCDE";

	if ((fd1 = open("temp.foo", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0){
		printf("open file error\n");
		return 1;
	}
	if ((pid = fork()) < 0){
		perror("fork error\n");
		return 1;
	} else if (pid == 0){
		if ((fd2 = open("temp.foo", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0){
			printf("open file error\n");
			return 1;
		}
		if (lseek(fd2, 0, SEEK_END) == -1){
			perror("lseek error\n");
			return 1;
		}
		sleep(5);
		if (write(fd2, buf1, 5) != 5){
			perror("write error\n");
			return 1;
		}
	}
	sleep(2);
	if (lseek(fd1, 0, SEEK_END) == -1){
		perror("lseek error\n");
		return 1;
	}
	sleep(15);
	if (write(fd1, buf2, 5) != 5){
		perror("write error\n");
		return 1;
	}

	return 0;
}
