#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>
int main(int argc,char * argv[])
{
	int i;
	struct stat buf;
	char *ptr;
	for(i=1;i<argc;i++)
	{
		printf("%s: ",argv[i]);
		if(stat(argv[i],&buf)<0){
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
return 0;
}
/*
nayanareddy@ubuntu:~$ ./a.out *
5a1.c: regular
5a2.c: regular
5a.c: regular
5a.c~: regular
5b.c: regular
5b.c~: regular
6.c: regular
6.c~: regular
a.out: regular
c1.c: regular
c2.c: regular
c2.c~: regular
c3.c: regular
c4.c: regular
c5.c: regular
c.c: regular
co.c: regular
compare1.cpp: regular
compare.c: regular
compare.c~: regular
copy1.c: regular
copy2.c: regular
copy.c: regular
cp1.txt: regular
cp.c: regular
cp.c~: regular
cp.txt: regular
ct.c: regular
Desktop: directory
Documents: directory
Downloads: directory
examples.desktop: regular
f1.c: regular
f2.c: regular
file_type.c: regular
file_type.c~: regular
ls.c: regular
ls.c~: regular
Music: directory
new: directory
Pictures: directory
Public: directory
samp.c: regular
Templates: directory
Videos: directory
nayanareddy@ubuntu:~$ clear

*/
		
		
