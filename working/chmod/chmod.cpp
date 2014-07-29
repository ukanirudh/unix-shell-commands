#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main(int argc,char **argv)
{
	int flag=0;
	if(argc==3)
	{
			switch(argv[2][0])
			{
				case '1':
					flag=flag | S_IXUSR;
				break;
				
				case '2':
					flag=flag | S_IWUSR;
				break;

				case '3':
					flag=flag | S_IWUSR | S_IXUSR;
				break;
				
				case '4':
					flag=flag | S_IRUSR;
				break;
				
				case '5':
					flag=flag | S_IRUSR | S_IXUSR;
				break;
				
				case '6':
					flag=flag | S_IRUSR | S_IWUSR;
				break;
				
				case '7':
					flag=flag | S_IRWXU;
				break;
				
				default:
					cout<<"Wrong usage!!\n";
					break;			
			}			
			switch(argv[2][1])
			{
				case '1':
					flag=flag | S_IXGRP;
				break;
				
				case '2':
					flag=flag | S_IWGRP;
				break;

				case '3':
					flag=flag | S_IWGRP | S_IXGRP;
				break;
				
				case '4':
					flag=flag | S_IRGRP;
				break;
				
				case '5':
					flag=flag | S_IRGRP | S_IXGRP;
				break;
				
				case '6':
					flag=flag | S_IRGRP | S_IWGRP;
				break;
				
				case '7':
					flag=flag | S_IRWXG;
				break;
				
				default:
					cout<<"Wrong usage!!\n";
			 break;						
			}			
			switch(argv[2][2])
			{
				case '1':
					flag=flag | S_IXOTH;
				break;
				
				case '2':
					flag=flag | S_IWOTH;
				break;

				case '3':
					flag=flag | S_IWOTH | S_IXOTH;
				break;
				
				case '4':
					flag=flag | S_IROTH;
				break;
				
				case '5':
					flag=flag | S_IROTH | S_IXOTH;
				break;
				
				case '6':
					flag=flag | S_IROTH | S_IWOTH;
				break;
				
				case '7':
					flag=flag | S_IRWXO;
				break;
				
				default:
					cout<<"Wrong usage!!\n";
			break;						
			}			
			
			if(chmod(argv[1],flag))
				perror("chmod");
			else
				cout<<"Succesfully changed the permissions\n";		
	}
	else
		cout<<"Usage Error";
	return 0;
}
