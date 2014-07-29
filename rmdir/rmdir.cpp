#include<sys/stat.h>
#include<unistd.h>
#include<iostream>

using namespace std;

int main(int argc,char *argv[])
{
	if(argc>0)
	{
		
		int rc=rmdir(argv[1]);
		if(rc==0)
			cout<<"Successful\n";
		else
		{
			cout<<"Unsuccessfull\n";
			cout<<"Specified directory is not empty\n";
		}

	}
	else
		cout<<"Usage error\n";
	return 0;
}


