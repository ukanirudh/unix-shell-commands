#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

void main(int argc,char *argv[])
{

if(argc==1)
{
printf("error\n");
exit(0);
}


printf("...Deleting the file...\n");

int r=unlink(argv[1]);
if(r==0)
{
printf("success\n");
}

else printf("fail\n");

}
