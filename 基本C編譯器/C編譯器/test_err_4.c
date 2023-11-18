#include <stdlib.h>

char msg1="x";
char msg2="y";
char msg3="H";
char msg4="F";
int x,y,z,w;

int main()
{	
	x=9;
	y=12;
	if(y>x){
		z=y/x;
		w=y%x;
	}
	while(y>x){
		y=y-w;
		x=x+1;
	}
	printf("%s",msg1,x);
	printf("%s%d",msg2,y,z);
	printf("%d",msg3,z);
	printf("%s%d%c",msg4,w);
}


