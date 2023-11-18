#include <stdlib.h>

int a,b;
void kk(){
	a=a-b;
}
int main()
{
	a=6;
	b=2;
	kk();
	printf("%d\n",a);
	printf("%d\n",b);
	
}


