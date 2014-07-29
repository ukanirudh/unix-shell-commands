
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
	

	if(argc!=2)
	{
		printf("invalid!!\n");
		exit(0);
	}

	if(access(argv[1],F_OK)==0)
	{
		if(!chdir(argv[1]));
		printf("directory changed\n");

		
	}

	else
	{
		perror("access");
}
	return 0;
}
