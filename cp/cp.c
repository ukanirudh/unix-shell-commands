#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>


int main(int argc,char *argv[])
{
if(argc!=3)
{
printf("too few arguments\n");
exit(0);
}


int size,size1;
int fd,fd1;
char buf[100];

fd=open(argv[1],O_RDONLY);
fd1=open(argv[2],O_WRONLY|O_CREAT,0777);

size=read(fd,buf,100);
write(fd1,buf,size);

printf("%d ,bytes written to %s \n",size,argv[2]);

close(fd);
close(fd1);

return 0;
}
