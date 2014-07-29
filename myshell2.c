#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include <sys/utsname.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<time.h>
#include<utime.h>
#include<grp.h>
#include<signal.h>
#include<pwd.h>

#define BUF_SIZE 1024

void myln(char *token[]);
void mycp(char *token[]);
void mymv(char *token[]);
void mycat(char *token[]);
void mymkdir(char *token[]);
void mytouch(char *token[]);
void mycd(char *token[]);
void myls(char *token[]);
void myecho(char *token[]);
void mypwd();
void mydate();
void myuname(char *token[]);
void myhostname();

int i=0,fd1,fd2;
char buf[BUF_SIZE];
extern char **environ;

void myln(char *token[])
{
	if(i<3 || i>5)
	{
		printf("Invalid number of arguments!!\n");
		return;
	}
	if(strcmp(token[1],"-s")==0)
	{
		if(!symlink(token[2],token[3]))
			printf("Soft link created\n");
		else
			printf("Error creating symbolic link\n");
	}
	else if(i==3)
	{
		if(!link(token[1],token[2]))
			printf("Hard link created\n");
		else
			printf("Error creating hard link\n");
	}
	else 
		printf("Syntax error\n");
}

void mycat(char *token[])
{
	int x1,x2,x=1;
	if(i < 2)
	{
		perror("Invalid number of arguments!!\n");
		return;
	}
	
	while(x<i)
	{
		if(access(token[x],F_OK)==0)
		{
			fd1=open(token[x],O_RDONLY,0777);
			while((x1=read(fd1,buf,sizeof(buf))) > 0)
			{
				x2=write(1,buf,x1);
			}
			if(x1 < 0)
			{
				perror("error");
			}
			close(fd1);
		}
		else
			return ;
		x++;
	}
}

void myrm(char *token[])
{
	if(i < 2)
	{
		perror("Invalid number of arguments!!\n");
		return;
	}
	if(access(token[1],F_OK)==0)
	{
		if(unlink(token[1])==0)
		{
			printf("The file has been successfully removed\n");
		}
		else
			perror("error");
	}
	else
		perror("rm");	
}
void mycp(char *token[])
{
	int x1,x2;
	if(i != 3)
	{
		perror("Invalid number of arguments!!\n");
		return;
	}
	else if(access(token[1],F_OK)==0)
	{
		fd1=open(token[1],O_RDONLY,0777);
		fd2=open(token[2],O_RDWR|O_CREAT|O_EXCL,0777);
		while((x1=read(fd1,buf,sizeof(buf))) > 0)
		{
			x2=write(fd2,buf,x1);
		}
		close(fd1);
		if(x2 > 0)
		{
			printf("Copying of file successful\n");
		}
		else
			perror("error");
		close(fd2);
	}
	else
		perror("cp");
}

void mymv(char *token[])
{
	if(i!=3)
	{
		printf("Invalid number of arguments!!\n");
		return;
	}
	else if(access(token[2],F_OK)!=0)
	{
		fd1=open(token[1],O_RDWR|O_CREAT|O_EXCL);
		if(!link(token[1],token[2]))
		{
			if(!unlink(token[1]))
			{
				printf("The file has been moved.\n");
			}
		}
		else
			perror("mv");
		close(fd1);
	}
	else
		perror("error");
}

void mymkdir(char *token[])
{
	int x=1,y;
	if(i<2)
	{
		printf("Invalid number of arguments!!\n");
		return;
	}
	while(x < i)
	{		
		y=mkdir(token[x],S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
		if(y<0)
		{
			perror("mkdir");
		}
		x++;	
	}

}

void mycd(char *token[])
{
	if(i != 2)
	{
		perror("Invalid number of arguments!!\n");
		return;
	}
	if(chdir(token[1])!=0)
	{
		perror("cd");
	}
	
}

void myls(char *token[])
{
	DIR *dir1;
	struct dirent *dir;
	struct stat buf;
	char name[100],user[100];
	if(i == 1 || i == 2)
	{
		if(strcmp(token[1],".")==0 || i == 1)
		{
			if((dir1=opendir("."))== NULL)
			{
				perror("ls");
			}
			else
			{
				while((dir=readdir(dir1)) != NULL)
				{
					printf("%s\n",dir->d_name);
				}
				printf("\n");
			}
		}
		else if(access(token[1],F_OK)==0)
		{
			printf("%s\n",token[1]);
		}
		else if(strcmp(token[1],"-l")==0)
		{
			if((dir1=opendir("."))== NULL)
			{
				perror("ls");
			}
			else
			{
				while((dir=readdir(dir1)) != NULL)
				{
					
					if(stat(dir->d_name,&buf)==0)
					{

							printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    							printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    							printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    							printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    							printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    							printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    							printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    							printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    							printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    							printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
							printf(" %2d %s %2s %5d %10s %2s",(int)buf.st_nlink,getlogin(),getlogin(),(int)buf.st_size,dir->d_name,ctime(&buf.st_ctime));
					}
					else
					{
						perror("ls -l");
						return;
					}
				}
			}
		}
		
	}
	else if(i == 3)
	{
		if(access(token[2],F_OK)==0)
		{
			if((dir1=opendir("."))== NULL)
			{
				perror("ls");
			}
			else
			{
				while((dir=readdir(dir1)) != NULL)
				{
					
					if(stat(dir->d_name,&buf)==0)
					{
							printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    							printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    							printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    							printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    							printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    							printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    							printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    							printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    							printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    							printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
							printf(" %2d %s %2s %5d %10s %2s",(int)buf.st_nlink,getlogin(),getlogin(),(int)buf.st_size,dir->d_name,ctime(&buf.st_ctime));
						
					}
					else
					{
						perror("ls -l");
						return;
					}
				}
			}
		}
	}



if(strcmp(token[1],"-i")==0)
{
//printf("hi");

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

}


if(strcmp(token[1],"-li")==0)
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


}




	/*else
	{
		perror("Invalid no of arguments!!\n");
		return;
	}*/
}

void mytouch(char *token[])
{
	time_t *t;
	struct stat buf;
	if(i != 2)
	{
		perror("Invalid no of arguments!!\n");
		return;
	}
	if(access(token[1],F_OK)==0)
	{
		utime(token[1],NULL);	
	}
	else
	{
		fd1=open(token[1],O_RDWR|O_CREAT,0777);
		close(fd1);
	}
}

void myrmdir(char *token[])
{
	if(i>0)
	{
		
		int rc=rmdir(token[1]);
		if(rc==0)
			printf("Successful\n");
		else
		{
			printf("Unsuccessfull\n");
			printf("Specified directory is not empty\n");
		}

	}
	else
		printf("Usage error\n");
}

void mytime()
{
	time_t t = time(NULL);
        struct tm tm = *localtime(&t);
	printf("The time is: %d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

}
void mypwd()
{
	char buf[200];
	getcwd(buf,sizeof(buf));
	printf("%s\n",buf);	
}

void mydate()
{
	time_t t = time(NULL);
        struct tm tm1 = *localtime(&t);
	tm1.tm_year=tm1.tm_year + 1900;
	tm1.tm_mon=tm1.tm_mon + 1;
	 printf("%s\n",asctime(localtime(&t)));
}

void myuname(char *token[])
{
	struct utsname buf;
	
	if(i>2)
	{
		printf("invalid\n");
		error(0);
	}
	if(i == 2)
	{
		if(strcmp(token[1],"-a")==0)
		{
			if(uname(&buf)==0)
			printf("%s %s %s %s %s \n",buf.sysname,buf.nodename,buf.release,buf.version,buf.machine);
			else
			perror("error");
		}
	}
	else if(i == 1)
	{
		if(uname(&buf)==0)
		printf("%s\n",buf.sysname);
		else
		perror("error");
	}
}



void mykill(char *token[])
{    if (i < 2)
    {
        printf("usage: ./kill PID");
    }
else
    kill(atoi(token[1]), SIGKILL);


}



void mywc(char *token[] )
{
 int character_count = 0;
           int space_count = 0;
           int word_count = 0;
           int line_count = 0;
           char ch;

           FILE *fp;
           fp = fopen(token[1],"r");

           if(i == 0)
           {
   printf("Please specify the filename as argument\n");
                      exit(0);
           }

           


           while((ch=fgetc(fp))!=EOF)
           {
                       character_count++;
                       if(ch == ' ')
                       {
                             space_count++;
                             word_count++;
                       }
                       if(ch == '\n')
                       {
line_count++;
                       }
           }
           printf("character_count = %d\n",character_count);
           printf("space_count = %d\n",space_count);
           printf("word_count = %d\n",word_count+1);
           printf("line_count = %d\n",line_count);
}


void myfiletype(char *token[])
{
	int j;
	struct stat buf;
	char *ptr;
	for(j=1;j<i;j++)
	{
		printf("%s: ",token[j]);
		if(stat(token[j],&buf)<0){
		perror("stat");	
		}
		if(S_ISREG(buf.st_mode))
			ptr="regular";
		else if(S_ISDIR(buf.st_mode))
			ptr="directory";
		else if(S_ISCHR(buf.st_mode))
			ptr="character special";
		else if(S_ISBLK(buf.st_mode))
			ptr="block special";
		else if(S_ISFIFO(buf.st_mode))
			ptr="fifo";
		else if(S_ISLNK(buf.st_mode))
			ptr="symbolic link";
		else if(S_ISSOCK(buf.st_mode))
			ptr="socket";
		else
			ptr="unknown mode";
			printf("%s\n",ptr);
	}

}






int main(int argc,char *argv[])
{
	char *token[100],str[100],*str1,*token1,*ptr;
	printf("ukanirudh:");
	printf(get_current_dir_name());	
	printf("\n\nWELCOME TO MYSHELL\n\n");
	while(1)
	{
		
		printf(get_current_dir_name());	

		printf(":MYSHELL>> ");
		str1=gets(str);
		for(i=0;;str1=NULL,i++)
		{
			token1=strtok(str1," ");
			if(token1 == NULL)
				break;
			token[i]=token1;
			
		}
		if(token[0] == NULL)
		{
			continue;
		}
		else
		{
			if(strcmp(token[0],"exit")==0)
			{
				_exit(1);
			}
			else if(strcmp(token[0],"ln")==0)
			{
				myln(token);
			}
			else if(strcmp(token[0],"cp")==0)
			{
				mycp(token);
			}
			else if(strcmp(token[0],"cat")==0)
			{
				mycat(token);
			}
			else if(strcmp(token[0],"rm")==0)
			{
				myrm(token);
			}
			else if(strcmp(token[0],"mv")==0)
			{
				mymv(token);
			}
			else if(strcmp(token[0],"mkdir")==0)
			{
				mymkdir(token);
			}
			else if(strcmp(token[0],"cd")==0)
			{
				mycd(token);
			}
			else if(strcmp(token[0],"ls")==0)
			{
				myls(token);
			}
			else if(strcmp(token[0],"touch")==0)
			{
				mytouch(token);
			}
			else if(strcmp(token[0],"rmdir")==0)
			{
				myrmdir(token);
			}
			
			else if(strcmp(token[0],"pwd")==0)
			{
				mypwd();
			}
			else if(strcmp(token[0],"date")==0)
			{
				mydate();
			}
			else if(strcmp(token[0],"uname")==0)
			{
				myuname(token);
			}


			else if(strcmp(token[0],"kill")==0)
			{
				mykill(token);
			}

			else if(strcmp(token[0],"wc")==0)
			{
				mywc(token);
			}


			else if(strcmp(token[0],"time")==0)
			{
				mytime();
			}

			else if(strcmp(token[0],"filetype")==0)
			{
				myfiletype(token);
			}



			else if(token[1][0]=='\0')
			{	
			}
			else
			{
				printf("%s : Command not found\n",token[0]);
			}
		}
	}
	return 0;
}
