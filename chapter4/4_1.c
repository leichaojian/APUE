/************************
  递归目录，判断不同的文件类型各占多大百分比
  ************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#define MAXSIZE 1024

int	nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;
void findFile(char *);

int main(int argc, char **argv)
{
	if (argc != 2){
		printf("usage:a.out<descriptor#>");
		return 1;
	}

	findFile(argv[1]);

	printf("regular file:%7d---%5.2f\n", nreg, nreg * 100.0 / ntot);
	printf("directory file:%7d---%5.2f\n", ndir, ndir * 100.0 / ntot);
	printf("character special file:%7d---%5.2f\n", nchr, nchr * 100.0 / ntot);
	printf("fifo file:%7d---%5.2f\n", nfifo, nfifo * 100.0 / ntot);
	printf("link file:%7d---%5.2f\n", nslink, nslink * 100.0 / ntot);
	printf("socket file:%7d---%5.2f\n", nsock, nsock * 100.0 / ntot);
	printf("block file:%7d---%5.2f\n", nblk, nblk * 100.0 / ntot);

	return 0;
}

void findFile(char *path)
{
	struct stat	status;
	char	dirent[MAXSIZE];
	DIR		*dp;
	struct	dirent *dirp;
	char	slash[2] = "/";

	ntot++;
	if (lstat(path, &status) < 0){
		perror("lstat error\n");
		printf("path is:%s\n", path);
		return;
	}
	if (S_ISREG(status.st_mode))	nreg++;
	else if (S_ISCHR(status.st_mode))	nchr++;
	else if (S_ISBLK(status.st_mode))	nblk++;
	else if (S_ISFIFO(status.st_mode))	nfifo++;
	else if (S_ISLNK(status.st_mode))	nslink++;
	else if (S_ISSOCK(status.st_mode))	nsock++;
	else if (S_ISDIR(status.st_mode)){
		ndir++;
		if ((dp = opendir(path)) == NULL){
			perror("open directory error\n");
			printf("the directory is:%s\n", path);
			return;
		}
		while ((dirp = readdir(dp)) != NULL){
			if (strcmp(".", dirp->d_name) == 0 || strcmp("..", dirp->d_name) == 0){
				continue;
			}
			strcpy(dirent, path);
			strcpy(dirent + strlen(path), slash);
			strcpy(dirent + strlen(path) + strlen(slash), dirp->d_name);
			findFile(dirent);
		}
	}
}
