#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<ustat.h>
#include<time.h>
#include<utime.h>






int main(int argc,char ** argv)
{
struct utimbuf times;
	if(argc!=2)
	{
		printf("usage error\n");
		exit(0);
	}
	if(access(argv[1],F_OK)==0)
	{
		times.actime=times.modtime=time(0);
	}
	else
	{
	creat(argv[1],S_IRWXU);
	times.actime=times.modtime=time(0);
	}
	if(utime(argv[1],&times))
	{
		printf("error\n");
	}
	return 0;
}
