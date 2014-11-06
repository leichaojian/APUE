/******************
  access函数按照实际用户ID和实际组ID进行访问权限测试
  *******************/
#include <stdio.h>
#include <fcntl.h>
#include <error.h>

int main(int argc, char **argv)
{
	if (argc != 2){
		printf("usage:a.out <pathname>");
		return 1;
	}
	if (access(argv[1], R_OK) < 0){
		perror("access error\n");
		return 1;
	}
	else {
		printf ("read access ok\n");
	}

	if (open(argv[1], O_RDONLY) < 0){
		perror("open error");
	}
	else {
		printf ("open for reading OK\n");
	}

	return 0;
}
