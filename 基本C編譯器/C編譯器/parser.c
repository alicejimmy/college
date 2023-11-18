/*********************** parser.c **********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
** �ۭq���Y��
*/
#include "scanner.h"
#include "resword.h"
#include "err.h"
#include "followsym.h"
#include "idobj.h"
#include "idobjstack.h"
/*
** �ۭq�`��
*/
#define IDLEN      36
#define BUFSIZE   512
#define PROCDEPTH  36
/*
** �ۭq�禡�쫬
*/
void Identifier();
void Number();
void IdentifierList();
void Factor();
void Term();
void Expression();
void Condition();
void WhileStatement();
void IfStatement();
void CompoundStatement();
void AssignmentStatement();
void Statement();
void Block();
void ProgramHead();
void Program();

void Error();
void skip();
void IncludeWhate();
void CharDeclaration();
void IntDeclaration();
void VoidDeclaration();
void PrintfDeclaration();
/*
** �����ܼ�
*/
struct symbolTag *token;
int errorCount = 0;
struct idobjTag *idobj;
int level = -1;
char str[BUFSIZE];
/*
** Error()
*/
void Error(int n){
	int j;
	printf("****");
	for (j=0; j<token->right; j++){
		printf(" ");
	}
	sprintf(str, "^%d  %s\n",n, errmsgs[n]);
    printf(str);
    errorCount++;
}
/*
** checkexist()
*/
int checkexist(){
	idobj=getIdobj(token->value);
	if (idobj==NULL){
		return 0;
	}
	else{
		return 1;
	}
}
/*
** skip()
*/
void skip(char follows[], int n){
    if (follows[token->sym]==0){
		Error(n);
		while (follows[token->sym]==0){
			token = nextToken();
		}
    }
}
/*
** �y�k�W�h#1 <Program>
*/
void Program(){
	ProgramHead();
	Block();
}
/*
** �y�k�W�h#2 <ProgramHead>
*/
void ProgramHead(){
	if (token->sym == symHASHTAG){
		token = nextToken();
	}
	else{
		Error(1);
	}
	if (strcmp(token->value,"include")==0){
		token = nextToken();
	}
	else{
		Error(2);
	}
	if (token->sym == symLESS){
		token = nextToken();
	}
	else{
		Error(3);
	}
	IncludeWhate();
	if (token->sym == symGREATER){
		token = nextToken();
	}
	else{
		Error(3);
	}
}
void IncludeWhate(){
	if (strcmp(token->value, "stdlib")==0){
		token = nextToken();
	}
	else if (strcmp(token->value, "stdio")==0){
		token = nextToken();
	}
	else{
		Error(4);
	}
	if (token->sym == symPERIOD){
		token = nextToken();
	}
	else{
		Error(4);
	}
	if (strcmp(token->value, "h")==0){
		token = nextToken();
	}
	else{
		Error(4);
	}
}
/*
** �y�k�W�h#3 <Block>
*/
void Block(){
	level++;
	if (strcmp(token->value, "char")==0){
		CharDeclaration();
		token = nextToken();
	}
	else if (strcmp(token->value, "int")==0){
		IntDeclaration();
		if(strcmp(token->value, "main")==0){
			token = nextToken();
			if (token->sym == symLPAREN){
				token = nextToken();
			}
			else{
				Error(11);
			}
			if (token->sym == symRPAREN){
				token = nextToken();
				CompoundStatement();
				return;
			}
			else{
				Error(10);
			}
		}
		token = nextToken();
	}
	else if (strcmp(token->value, "void")==0){
		VoidDeclaration();
		token = nextToken();
	}
	else{
		Error(0);
		skip(block, 15);
		token = nextToken();
	}
	level--;
	Block();
}
/*
** �y�k�W�h#4(��) <CharDeclaration>
*/

void CharDeclaration(){
	int num=1,NUM=1;//�r��ƶq,�}�C�Ʀr 
	if (strcmp(token->value, "char")==0){
		token = nextToken();
		if (token->sym == symIDENTIFIER){
	        if (checkexist()){
	        	Error(18);
			} 
	        idobj = newIdobj(token->value, token->sym, symchar, level);
	        idobjpush(idobj);
	        token = nextToken();
	    }
		if (token->sym == symLBRACKE){
			token = nextToken();
			NUM=atoi(token->value);
			Number(); 
			if (token->sym == symRBRACKE){
				token = nextToken();
			}
			else{
				Error(6);
			}
		}
		if (token->sym == symBECOMES){
			token = nextToken();
			if (token->sym == symCHAR){
				num=strlen(token->value);
				token = nextToken();
			}
			else if(token->sym == symSTRING){
				num=strlen(token->value);
				token = nextToken();
			}
			else{
				Error(0);
			}  
			if(num>NUM){
				Error(8);
			}
		}
	
		while (token->sym == symCOMMA){
			token = nextToken();
			if (token->sym == symIDENTIFIER){
		        if (checkexist()){
		        	Error(18);
				} 
		        idobj = newIdobj(token->value, token->sym, symchar, level);
		        idobjpush(idobj);
		        token = nextToken();
		    }
			if (token->sym == symLBRACKE){
				token = nextToken();
				NUM=atoi(token->value);
				Number(); 
				if (token->sym == symRBRACKE){
					token = nextToken();
				}
				else{
					Error(6);
				}
			}
			if (token->sym == symBECOMES){
				token = nextToken();
				if (token->sym == symCHAR){
					num=strlen(token->value);
					token = nextToken();
				}
				else if(token->sym == symSTRING){
					num=strlen(token->value);
					token = nextToken();
				}
				else{
					Error(0);
				}  
				if(num>NUM){
					Error(8);
				}
			}
		}
		if (token->sym == symSEMI){
			//token = nextToken();
		}
		else{
			Error(9);
		}
	}
	else{
		Error(0);
	}
	
}
/*
** �y�k�W�h#5(��) <IntDeclaration>
*/
void IntDeclaration(){
	if (strcmp(token->value, "int")==0){
		token = nextToken();
		if(strcmp(token->value, "main")==0){
			return;
		}
	}
	else{
		Error(0);
	}
	if (token->sym == symIDENTIFIER){
        if (checkexist()){
        	Error(19);
		} 
        idobj = newIdobj(token->value, token->sym, symINT, level);
        idobjpush(idobj);
        token = nextToken();
    }
	if (token->sym == symBECOMES){
		token = nextToken();
		Expression();
	}  
	while (token->sym == symCOMMA){
		token = nextToken();
		if (token->sym == symIDENTIFIER){
	        if (checkexist()){
	        	Error(19);
			} 
	        idobj = newIdobj(token->value, token->sym, symINT, level);
	        idobjpush(idobj);
	        token = nextToken();
	    }
		if (token->sym == symBECOMES){
			token = nextToken();
			Expression();
		}  
	}
	if (token->sym == symSEMI){
		//token = nextToken();
	}
	else{
		Error(0);
	}
}
/*
** �y�k�W�h#6(��) <VoidDeclaration>
*/
void VoidDeclaration(){
	int i=0;
	if (strcmp(token->value, "void")==0){
		token = nextToken();
		if (token->sym == symIDENTIFIER){
	        if (checkexist()){
	        	Error(20);
			} 
	        idobj = newIdobj(token->value, token->sym, symVOID, level);
	        idobjpush(idobj);
	        token = nextToken();
	    }
		if (token->sym == symLPAREN){
			token = nextToken();
			if (token->sym == symRPAREN){
				token = nextToken();
				CompoundStatement();
			}
			else{
				Error(0);
			}
		}
		else{
			Error(0);
		}
		
	}
}
/*
** �y�k�W�h#7 <Statement>
*/
void Statement(){
    if (isResword(token->value) != -1){
		if (strcmp(token->value,"if")==0){
			IfStatement();
		}
		else if (strcmp(token->value,"while")==0){
			WhileStatement();
		}
		else if (strcmp(token->value,"char")==0){
			CharDeclaration();
		}
		else if (strcmp(token->value,"int")==0){
			IntDeclaration();
		}
		else if (strcmp(token->value,"printf")==0){
			PrintfDeclaration();
		}
		
    }
    else if (token->sym == symIDENTIFIER){
    	AssignmentStatement();
	}
	else if (token->sym == symRBRACES){
		
	}
	else{
		skip(statement, 15);
	}
}
/*
** �y�k�W�h#8 <AssignmentStatement>
*/
void AssignmentStatement(){
    Identifier();
    if (token->sym == symBECOMES){
    	token = nextToken();
    	Expression();
	}
	else if (token->sym == symLPAREN){
		token = nextToken();
		if (token->sym == symRPAREN){
			token = nextToken();
			if (token->sym == symSEMI){
				return;
			}
			else{
				Error(9);
			}
		}
		else{
			Error(10);
		}
	}
}
/*
** �y�k�W�h#10 <CompoundStatement>
*/
void CompoundStatement(){
	
	int braces=0;//�j�A���ƶq 
    if (token->sym == symLBRACES){
    	level++;
    	braces++; 
    	token = nextToken();
    	while (braces>0){
			Statement();
			token = nextToken();
			if(token->sym == symRBRACES){
				braces--;
				level--;
			}		
	    }
	}
    else{
    	Error(12);
    	skip(statement, 15);
	}
    
}
/*
** �y�k�W�h#11 <IfStatement>
*/
void IfStatement(){
    if (strcmp(token->value,"if")==0){
    	token = nextToken();
    	Condition();
    	CompoundStatement();
	}
    else{
    	Error(0);
    	skip(statement, 15);
	}
    
}
/*
** �y�k�W�h#12 <WhileStatement>
*/
void WhileStatement(){
    if (strcmp(token->value,"while")==0){
    	token = nextToken();
    	Condition();
    	CompoundStatement();
	}
    else{
    	Error(0);
    	skip(statement, 15);
	}
    
}
/*
** �y�k�W�h#13 <printfDeclaration>
*/
void PrintfDeclaration(){
	int printnum=0;//��X�ܼƪ��ƶq 
	int i=0;
    if (strcmp(token->value,"printf")==0){
    	token = nextToken();
    	if(token->sym == symLPAREN){
    		token = nextToken();
    		if(token->sym == symSTRING){
    			for(i=0;i<strlen(token->value);i++){
    				if(token->value[i]=='%'){
    					if(token->value[i+1]=='d'||token->value[i+1]=='c'||token->value[i+1]=='s'){
    						printnum++;
						}
					}
				}
	    		token = nextToken();
	    		while(printnum>0){
	    			if(token->sym == symCOMMA){
		    			token = nextToken();
		    			if (token->sym == symIDENTIFIER){
							//token = nextToken();
							Identifier();
						}
						else{
							Error(5);
						}
					}
					else{
						Error(17);
					}
					printnum--;
				}
	    		if(token->sym == symRPAREN){
	    			token = nextToken();
	    			if (token->sym == symSEMI){
						//token = nextToken();
					}
					else{
						Error(9);
					}
				}
				else{
					Error(10);
				}
			}
			else{
				Error(16);
			}
		}
    	
		else{
			Error(11);
		}
	}
    else{
    	Error(0);
    	skip(statement, 15);
	}
    
}
/*
** �y�k�W�h#15 <IdentifierList>
*/
void IdentifierList(){
    Identifier();
    while (token->sym == symCOMMA){
		token = nextToken();
		Identifier();
    }
}
/*
** �y�k�W�h#16 <Condition>
*/
void Condition(){
	if (token->sym == symLPAREN){
    	token = nextToken();
    	Expression();
	    if (token->sym == symLESS ||token->sym == symLEQ ||token->sym == symEQ ||token->sym == symNEQ ||token->sym == symGREATER ||token->sym == symGEQ){
	    	token = nextToken();
	    	Expression();
	    	if (token->sym == symRPAREN){
		    	token = nextToken();
			}
		    else{
		    	Error(10);
			}
		}
	    else{
	    	Error(14);
	    	skip(condition, 15);
		}
	    
	}
    else{
    	Error(11);
	}
    
}
/*
** �y�k�W�h#17 <Expression>
*/
void Expression(){
    if (token->sym == symPLUS ||token->sym == symMINUS){
    	token = nextToken();
	}
	Term();
    while (token->sym == symPLUS ||token->sym == symMINUS){
		token = nextToken();
		Term();
	}
}
/*
** �y�k�W�h#18 <Term>
*/
void Term(){
    Factor();
    while (token->sym == symMUL ||token->sym == symDIV ||token->sym == symDIVREM){
		token = nextToken();
		Factor();
    }
}
/*
** �y�k�W�h#19 <Factor>
*/
void Factor(){
    if (token->sym == symIDENTIFIER){
    	Identifier();
	}
    else if (token->sym == symNUMBER){
    	Number();
	}
    else if (token->sym == symLPAREN){
    	token = nextToken();
    	Expression();
    	if (token->sym == symRPAREN){
    		token = nextToken();
		}
		else{
			Error(10);
			skip(factor, 15);
		} 
    }
    else{
    	Error(0);
    	skip(factor, 15);
	}
}
/*
** �ѧO�r�ŰO�B�z
*/
void Identifier(){
	if (token->sym == symIDENTIFIER){
		idobj=getIdobj(token->value);
		if (idobj == NULL){
			Error(21);
		}
		token = nextToken();
	}
	else{
		Error(5);
	}
}
/*
** �Ʀr�ŰO�B�z
*/
void Number(){
    if (token->sym == symNUMBER){
    	token = nextToken();
	}
    else{
    	Error(7);
	}
}
/*
************************** �D�{�� **********************
*/
int main(int argc, char *argv[]){
	char openfile[20]="";
	printf("�п�J�n���檺�ɦW�G\n");
	scanf("%s",&openfile);
    FILE *f=fopen(openfile, "r");
    scanner(f);
    followsyminit();
    token = nextToken();
    Program();
    fclose(f);
    printf("\n  Plone compile completed.\n  Error count : %d\n", errorCount);
    printf("\n�ѧO�r���c���|���e�p�U�G\n%s\n", idobjstackToString());
    return 0;
}
