#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{
char buf[250];
int ac=argc;
int fdesc,len;
int i=0;
for(i=0;i<ac;i++)
{
	fdesc=open(argv[i],O_RDONLY|O_EXCL);
	while(len=read(fdesc,buf,argv[i]))
	write(1,buf,len);
	close(fdesc);
}
return 0;
}
