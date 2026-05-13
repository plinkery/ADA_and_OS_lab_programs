#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	DIR* dp;
	struct dirent* dirp;
	if (argc<2)
		{
			printf("\n you are not passing the directory\n");
			exit(1);
		}
		if (( dp=opendir(argv[1])) == NULL)
			{
				printf("\n cannot open it doesn't exist %s file \n",argv[1]);
				exit(1);
			}
			while (( dirp=readdir(dp)) != NULL )
			{
				printf ("%s\n", dirp->d_name);
			}
				closedir(dp);
			return 0;	
}
