

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
#include<grp.h>
#include<signal.h>



int main(int argc,char *argv[] )
{
 int character_count = 0;
           int space_count = 0;
           int word_count = 0;
           int line_count = 0;
           char ch;

           FILE *fp;
           fp = fopen(argv[1],"r");

           if(argc == 0)
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

