#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{
char buf[250];
int fdesc,len;

if(argc>0)
{
if(access(argv[1],F_OK))
{
fdesc=open(argv[1],O_WRONLY|O_CREAT,0744);
write(fdesc,"helloworld\n",12);
}

else
{
fdesc=open(argv[1],O_RDONLY);
while(len=read(fdesc,buf,256))
	write(1,buf,len);
}
}
close(fdesc);

return 0;

}
