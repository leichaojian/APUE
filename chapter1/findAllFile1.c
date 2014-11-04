/***********************
  列举指定目录下的所有文件:通过stat来判断是否为文件还是目录
  **********************/
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#define MAXSIZE 1024

void showAllFile(char *path);
int main(int argc, char **argv)
{
	if (argc != 2){
		printf("usage:ls directory_name\n");
		return 1;
	}

	showAllFile(argv[1]);

	return 0;
}
void showAllFile(char *path)
{
	DIR		*dp;
	struct	dirent *dirp;
	char	dirent[MAXSIZE];
	char	slash[2] = "/";
	struct	stat	buf;
	if (lstat(path, &buf) < 0){
		return;
	}
	if (!S_ISDIR(buf.st_mode)){
		printf("%s\n", path);
	}
	else {
		dp = opendir(path);
		while ((dirp = readdir(dp)) != NULL){
			if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0){
				continue;
			}
			strcpy(dirent, path);
			strcpy(dirent + strlen(path), slash);
			strcpy(dirent + strlen(path) + strlen(slash), dirp->d_name);
			if (lstat(dirent, &buf) < 0){
				continue;
			}
			if (!S_ISDIR(buf.st_mode)){
				printf("%s\n", dirent);
			}
			else {
				showAllFile(dirent);
			}
		}
	}
}
