/***********************
  从标准输入读命令并执行
  ***********************/
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <error.h>

#define MAXLINE 1024

static void sig_int(int);

int main(void)
{
	char	buf[MAXLINE];
	pid_t	pid;
	int		status;

	if (signal(SIGINT, sig_int) == SIG_ERR){
		perror("signal error");
		return 1;
	}	
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
void sig_int(int signo)
{
	printf("interrupt\n");
}
