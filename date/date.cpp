#include <time.h>
#include <iostream>

using namespace std;
int main()
{
	time_t timv=time(0);
	struct tm *ist=localtime(&timv);
	cout<<"IST "<<asctime(ist);
	return 0;
}
