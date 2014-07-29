#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>



int main(int argc,char *argv[])
{
	char buf[100];
	if(argc!=1)
	{
		printf("invalid number of arguments\n");
		exit(0);
	}
	else
	{
		getcwd(buf,sizeof(buf));
		printf("%s\n",buf);
	}
	return 0;
}


