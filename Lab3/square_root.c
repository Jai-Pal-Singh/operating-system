#include "square_root.h"
int main(int argv,char *argc[])
{
	if(argv==2)
		printf("%f\n",sqrt(atoi(argc[1])));
	return 0;
}
