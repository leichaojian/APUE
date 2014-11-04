#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
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
	//说明为一个文件
	if ((dp = opendir(path)) == NULL){
		printf("%s\n", path);
	}
	else{
		while ((dirp = readdir(dp)) != NULL){
			if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0){
				continue;
			}
			strcpy(dirent, path);
			strcpy(dirent + strlen(path), slash);
			strcpy(dirent + strlen(path) + strlen(slash), dirp->d_name);
			showAllFile(dirent);
		}
	}
}
