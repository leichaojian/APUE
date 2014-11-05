/**********
  调用open,read,write,close的实例
  其中，使用dup2将文件描述符进行复制，即操作fd1就是操作STDIN_FILENO，操作fd2就是操作STDOUT_FILENO
  ************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 4096
int main(void)
{
	int	fd1;
	int	fd2;
	int	n;
	char	buf[BUFFSIZE];

	dup2(STDIN_FILENO, fd1);
	//如果把STDOUT_FILENO和fd2关联起来，则无法执行./a.out <3_3.c这样的操作，为什么？
//	dup2(STDOUT_FILENO, fd2);

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
		if (write(STDOUT_FILENO, buf, n) != n){
			perror("write error\n");
			return 1;
		}
	}
	if (n < 0){
		perror("read error\n");
		return 1;
	}

	return 0;
}
