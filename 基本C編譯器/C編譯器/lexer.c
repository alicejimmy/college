/********************* lexer.c *******************/
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
struct symbolTag *token;
int main(int argc, char *argv[]) {
	char openfile[20]="";
	printf("�п�J�n���檺�ɦW�G\n");
	scanf("%s",&openfile);
	FILE *f=fopen(openfile, "r");
	scanner(f);
	while ((token=nextToken())!=NULL) {
    	if (token->sym==symerror || argc==3) {
      		if (token->sym==symerror){
        		printf("***���~***");
    		}
    	}
    	else{
    		printf("          ");
		}
        printf("�ŰO�s��=%d\t�C��=%d\t�渹=%d\t�ŰO�W��=\"%s\"\n", token->sym, token->left, token->right, token->value);
	}
  	fclose(f);
  	printf("\n  �y�J���R�����C");
  	return 0;
}

/*�ŰO�s��
0
1  ���~(�S�X�{�b�H�U���y�k)
2  �ܼ�(�^��a��z��A��Z�զX�Ӧ�)
3  �Ʀr(0��9�զX�Ӧ�)
4  �[��+
5  �-
6  ����*
7  ����/
8  ����==
9  ������!=
10 �p��<
11 �p�󵥩�<=
12 �j��>
13 �j�󵥩�>=
14 ���A��(
15 �k�A��)
16 �r��,
17 �����F
18 �y��.
19 ��=
	//20 �}�lBEGIN
	///21 ����END
	///22 ���]IF
	///23 �hTHEN
	///24 ��WHILE
	///25 ��DO
	///26 ŪREAD
	///27 �gWRITE
20///28 �_!
21///29 ���r��# 
	///30 const
22///31 �����A��[ 
23///32 �k���A��] 
	///33 �D�禡main 
24///34 �r�ꤺ�e(""�̭������e)
25///35 ���j�A��{
26///36 �k�j�A��}
27///37 ���l��%
28///(�s�[) �r�����e(''�̭������e)
	///38 char
	///39 int
	///40 printf
	///41 float
	///42 string
	///43 void 
*/
