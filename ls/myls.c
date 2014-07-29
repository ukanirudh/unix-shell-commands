#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
main(int argc,char *argv[])
{
	int flag, flag1, flag2;
	
	if(argc<2)
	{
		
		return myls();
	}
	else if(argc>2)
	{
		printf("\n\tmyls :: usage error\n");
		printf("\tcorrect usage :: myls -[OPTION]\n");
		printf("\t[OPTIONS] : [-l]\n\t            [-i]\n\t            [-li]\n\n");
	}	
	else 
	flag = strcmp(argv[1],"-i");
	if (flag==0)
	{
		return mylsi();
		
	}
	
	else 
	flag1 = strcmp(argv[1],"-l");
	if (flag1==0)
	{
		
		return mylsl();
		
	}	
	
	else
	{
		printf("\n\tmyls :: usage error\n");
		printf("\tcorrect usage :: myls -[OPTION]\n");
		printf("\t[OPTIONS] : [-l]\n\t\t    [-i]\n\t\t    [-li]\n\n");
	}	
	flag2 = strcmp(argv[1],"-li");
	if (flag2==0)
	{
		
		return mylsli();
	}
	else
	return 0;
}
myls()
{
	struct passwd *pwd = calloc(1, sizeof(struct passwd));
	struct dirent *p;
	DIR *dp;
	struct stat b;
	dp=opendir(".");
	if(dp==NULL)
	{
		printf("\nopendir :: Directory opening problem\n");
		return;
	}
	while((p=readdir(dp))!=NULL)
	{	
		printf("\t%s\n",p->d_name);
	}
	closedir(dp);
	rewinddir(dp);
	exit(0);
}

mylsi()
{
	struct passwd *pwd = calloc(1, sizeof(struct passwd));
	struct dirent *p;
	DIR *dp;
	struct stat b;
	dp=opendir(".");
	if(dp==NULL)
	{
		printf("\nopendir :: Directory opening problem\n");
		return;
	}
	while((p=readdir(dp))!=NULL)
	{	
		printf(" %6ld ",p->d_ino);		
		printf(" %s\n",p->d_name);
	}
	closedir(dp);
	rewinddir(dp);
	exit(0);
}

mylsl()
{
	struct passwd *pwd = calloc(1, sizeof(struct passwd));
	struct dirent *p;
	DIR *dp;
	struct stat b;
	
		dp=opendir(".");
		if(dp==NULL)
		{
			printf("\nopendir :: Directory opening problem\n");
			return;
		}
		while((p=readdir(dp))!=NULL)
		{	
			if(stat(p->d_name,&b)<0)
			{
				printf("\nStat failure \n");
				exit(0);
			}
			switch(b.st_mode & S_IFMT )
			{
				case S_IFREG:
				printf("-");
				break;

				case S_IFDIR:
				printf("d");
				break;

				case S_IFCHR:
				printf("c");
				break;

				case S_IFBLK:
				printf("b");
				break;

				case S_IFLNK:
				printf("l");
				break;

				case S_IFSOCK:
				printf("s");
				break;
				case S_IFIFO:
				printf("p");
				break;

			}
			if(S_IRUSR & b.st_mode)
			printf("r");
			else
			printf("-");

			if(S_IWUSR & b.st_mode)
			printf("w");
			else
			printf("-");

			if(S_IXUSR & b.st_mode)
			printf("x");
			else
			printf("-");

			if(S_IRGRP & b.st_mode)
			printf("r");
			else
			printf("-");

			if(S_IWGRP & b.st_mode)
			printf("w");
			else
			printf("-");

			if(S_IXGRP & b.st_mode)
			printf("x");
			else
			printf("-");

			if(S_IROTH & b.st_mode)
			printf("r");
			else
			printf("-");

			if(S_IWOTH & b.st_mode)
			printf("w");
			else
			printf("-");

			if(S_IXOTH & b.st_mode)
			printf("x");
			else
			printf("-");

			printf("%3ld ",b.st_nlink);
			printf("%4d ",b.st_uid);
			printf("%4d ",b.st_gid);
			printf("%6ld ",b.st_size);
			printf("%10s ",ctime(&b.st_ctime));
			printf("%s\n",p->d_name);
			
		}
		closedir(dp);
		rewinddir(dp);
		exit(0);
}


mylsli()
{
	struct passwd *pwd = calloc(1, sizeof(struct passwd));
	struct dirent *p;
	DIR *dp;
	struct stat b;
	
		dp=opendir(".");
		if(dp==NULL)
		{
			printf("\nopendir :: Directory opening problem\n");
			return;
		}
		while((p=readdir(dp))!=NULL)
		{	
			if(stat(p->d_name,&b)<0)
			{
				printf("\nStat failure \n");
				exit(0);
			}
			switch(b.st_mode & S_IFMT )
			{
				case S_IFREG:
				printf("-");
				break;

				case S_IFDIR:
				printf("d");
				break;

				case S_IFCHR:
				printf("c");
				break;

				case S_IFBLK:
				printf("b");
				break;

				case S_IFLNK:
				printf("l");
				break;

				case S_IFSOCK:
				printf("s");
				break;
				case S_IFIFO:
				printf(" p");
				break;

			}
			if(S_IRUSR & b.st_mode)
			printf("r");
			else
			printf("-");

			if(S_IWUSR & b.st_mode)
			printf("w");
			else
			printf("-");

			if(S_IXUSR & b.st_mode)
			printf("x");
			else
			printf("-");

			if(S_IRGRP & b.st_mode)
			printf("r");
			else
			printf("-");

			if(S_IWGRP & b.st_mode)
			printf("w");
			else
			printf("-");

			if(S_IXGRP & b.st_mode)
			printf("x");
			else
			printf("-");

			if(S_IROTH & b.st_mode)
			printf("r");
			else
			printf("-");

			if(S_IWOTH & b.st_mode)
			printf("w");
			else
			printf("-");

			if(S_IXOTH & b.st_mode)
			printf("x");
			else
			printf("-");

			printf(" %3ld ",b.st_nlink);
			printf(" %4d ",b.st_uid);
			printf(" %4d ",b.st_gid);
			printf(" %6ld ",b.st_size);
			printf(" %10ld ",b.st_mtime);
			printf(" %6ld ",p->d_ino);
			printf(" %s\n",p->d_name);
		}
		closedir(dp);
		rewinddir(dp);
		exit(0);
}

