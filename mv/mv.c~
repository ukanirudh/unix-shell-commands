
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>


void main(int argc,char *argv[])
{
	int fd,fd1,r;
	char buf1[50],buf2[50];
	switch(argc)
	{
		case 1:
		printf("Error:No argv!");
		break;
		case 2:
		printf("Error:Too few argv for move command!");
		break;
		case 3:
		link(argv[1],argv[2]);
		unlink(argv[1]);
		printf("Contents of file %s moved to file %s\n",argv[1],argv[2]);
		break;
		default:
		printf("Error:Excess argv supplied!**!");
		break;
	}

}


