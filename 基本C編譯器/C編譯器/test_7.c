#include <stdlib.h>

int i=1;
int j=1;
int k;
int main()
{	
	while(i<=5){
		j=1;
		while(j<=5){
			k=i*j;
			printf("  ");
			printf("%d",i);
			printf("*");
			printf("%d",j);
			printf("=");
			printf("%d",k);
			j=j+1;
		}
		printf("\n"); 
		i=i+1;
	}
}


