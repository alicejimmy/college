/********************** resword.h ******************/
#include <stdlib.h>
#define RESWORDMAX 16
char reswords[RESWORDMAX][10] ={"BEGIN","END","if","THEN","while","DO","READ","WRITE","CONST","char","int","printf","float","string","void","include"};
int isResword(char *s){
	int i;
	for (i=0; i<RESWORDMAX; i++){
		if (strcmp(s, reswords[i]) == 0) {
			return i;
		}
	}
	return -1;
}
