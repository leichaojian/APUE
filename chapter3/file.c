/***********
  在多个进程中进行文件的共享
  ***********/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFSIZE 1000
int main(void)
{
	char buf1[BUFFSIZE];
	char buf2[BUFFSIZE];
	pid_t	pid;
	int	 fd;

	memset(buf1, 'a', BUFFSIZE);
	memset(buf2, 'b', BUFFSIZE);

	if ((fd = open("temp.foo", O_RDWR | O_CREAT | O_TRUNC, S_IR)))

}
