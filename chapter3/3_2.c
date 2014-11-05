/*************
  创建一个具有空洞的文件
  ****************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";
int main(void)
{
	int		fd;
	char	buf[16394];
	memset(buf, 'a', 16394);
	if ((fd = open("file.hole", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1){
		perror("open file error\n");
		return 1;
	}
	if (write(fd, buf1, 10) != 10){
		perror("buf1 write error\n");
		return 1;
	}
	if (lseek(fd, 16384, SEEK_SET) == -1){
		perror("lseek error\n");
		return 1;
	}
	if (write(fd, buf2, 10) != 10){
		perror("buf2 write error\n");
		return 1;
	}
	close(fd);

	if ((fd = open("file.nohole", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1){
		perror("open file error\n");
		return 1;
	}
	if (write(fd, buf, 16394) != 16394){
		perror("buf write error\n");
		return 1;
	}

	close(fd);

	return 0;
}
