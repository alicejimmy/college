#include <stdlib.h>

char msg1="x";
char msg2="y";
char msg3="H";
int x,y,z;

int main()
{	
	x=9;
	y=12;
	z=x**y;
	printf("%s%d",msg1,x);
	printf("%s%d",msg2,y);
	printf("%s%d",msg3,z);
	x--;
	printf("%s%d",msg1,x);
	y++;
	printf("%s%d",msg2,y);
	printf("%s%d",msg3,z);
}


