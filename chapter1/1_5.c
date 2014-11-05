/***********************
  从标准输入读命令并执行
  ***********************/
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLINE 1024

int main(void)
{
	char	buf[MAXLINE];
	pid_t	pid;
	int		status;

	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL){
		if (buf[strlen(buf) - 1] == '\n'){
			buf[strlen(buf) - 1] = '\0';
		}
		if ((pid = fork()) < 0){
			printf("fork error\n");
		} else if (0 == pid){
			execlp(buf, buf, (char *)0);
			printf("couldn't execute:%s", buf);
			exit(127);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0){
			printf("waitpid error\n");
		}
		printf("%% ");
	}

	return 0;
}
