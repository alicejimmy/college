/********************* lexer.c *******************/
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
struct symbolTag *token;
int main(int argc, char *argv[]) {
	char openfile[20]="";
	printf("請輸入要執行的檔名：\n");
	scanf("%s",&openfile);
	FILE *f=fopen(openfile, "r");
	scanner(f);
	while ((token=nextToken())!=NULL) {
    	if (token->sym==symerror || argc==3) {
      		if (token->sym==symerror){
        		printf("***錯誤***");
    		}
    	}
    	else{
    		printf("          ");
		}
        printf("符記編號=%d\t列號=%d\t行號=%d\t符記名稱=\"%s\"\n", token->sym, token->left, token->right, token->value);
	}
  	fclose(f);
  	printf("\n  語彙分析完成。");
  	return 0;
}

/*符記編號
0
1  錯誤(沒出現在以下的語法)
2  變數(英文a到z或A到Z組合而成)
3  數字(0到9組合而成)
4  加號+
5  減號-
6  乘號*
7  除號/
8  等於==
9  不等於!=
10 小於<
11 小於等於<=
12 大於>
13 大於等於>=
14 左括號(
15 右括號)
16 逗號,
17 分號；
18 句號.
19 為=
	//20 開始BEGIN
	///21 結束END
	///22 假設IF
	///23 則THEN
	///24 當WHILE
	///25 做DO
	///26 讀READ
	///27 寫WRITE
20///28 否!
21///29 井字號# 
	///30 const
22///31 左中括號[ 
23///32 右中括號] 
	///33 主函式main 
24///34 字串內容(""裡面的內容)
25///35 左大括號{
26///36 右大括號}
27///37 除餘數%
28///(新加) 字元內容(''裡面的內容)
	///38 char
	///39 int
	///40 printf
	///41 float
	///42 string
	///43 void 
*/
