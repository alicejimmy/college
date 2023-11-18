/*********************** parser.c **********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
** 自訂表頭檔
*/
#include "scanner.h"
#include "resword.h"
#include "err.h"
#include "followsym.h"
#include "idobj.h"
#include "idobjstack.h"
/*
** 自訂常數
*/
#define IDLEN      36
#define BUFSIZE   512
#define PROCDEPTH  36
/*
** 自訂函式原型
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
** 整體變數
*/
struct symbolTag *token;
int errorCount = 0;
struct idobjTag *idobj;
int level = -1;
int labelCount = 0;
char progname[IDLEN];
char outname[IDLEN];
FILE *outfile;
char buf[BUFSIZE];
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
** 語法規則#1 <Program>
*/
void Program(){
	//printf("!@#$%^&*\n");
	ProgramHead();
	Block();
}
/*
** 語法規則#2 <ProgramHead>
*/
void ProgramHead(){
	//printf("!@#$%^&*\n");
	strcat(outname, ".asm");
    outfile = fopen(outname, "w");
    ++labelCount;
    sprintf(buf,
          ";************** %s ****************\n"
          ";\n"
          "\tORG\t100H\n"
          "\tJMP\t_start%d\n"
          "_intstr\tDB\t'     ','$'\n"
          "_buf\tTIMES 256 DB ' '\n"
          "\tDB 13,10,'$'\n",
          outname, labelCount);
    fprintf(outfile, buf);
    
    strcpy(buf, "%include\t\"dispstr.mac\"\n");
    strcat(buf, "%include\t\"itostr.mac\"\n");
    strcat(buf, "%include\t\"readstr.mac\"\n");
    strcat(buf, "%include\t\"strtoi.mac\"\n");
    strcat(buf, "%include\t\"newline.mac\"\n");
    fputs(buf, outfile);
    
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
** 語法規則#3 <Block>
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
			sprintf(buf, "_start%d:\n", labelCount);
			//sprintf(buf, "_start%d:\n", 1);
    		fprintf(outfile, buf);
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
		sprintf(buf, "_start%d:\n", labelCount);
		fprintf(outfile, buf);
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
** 語法規則#4(改) <CharDeclaration>
*/

void CharDeclaration(){
	int num=1,NUM=1;//字串數量,陣列數字 
	char tmp[10]="";
	if (strcmp(token->value, "char")==0){
		token = nextToken();
		if (token->sym == symIDENTIFIER){
	        if (checkexist()){
	        	Error(18);
			} 
	        idobj = newIdobj(token->value, token->sym, symchar, level);
	        //sprintf(buf, "%s\tDW\t0\n", token->value);
        	//fprintf(outfile, buf);
	        idobjpush(idobj);
	        sprintf(buf, "\t%s\tDW\t'$'\n"
						 "\tMOV\tword[%s], ", token->value, token->value);
        	fprintf(outfile, buf);
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
				//sprintf(buf, "'%s','$'\n", token->value);
				sprintf(buf, "'%s$'\n", token->value);
        		fprintf(outfile, buf);

				token = nextToken();
			}
			else if(token->sym == symSTRING){
				num=strlen(token->value);
				//sprintf(buf, "'%s','$'\n", token->value);
				sprintf(buf, "'%s$'\n", token->value);
        		fprintf(outfile, buf);
				token = nextToken();
			}
			else{
				sprintf(buf, "'$'\n");
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
		        sprintf(buf, "%s\tDB\t", token->value);
            	fprintf(outfile, buf);
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
					sprintf(buf, "'%s','$'\n", token->value);
            		fprintf(outfile, buf);
					token = nextToken();
				}
				else if(token->sym == symSTRING){
					num=strlen(token->value);
					sprintf(buf, "'%s','$'\n", token->value);
            		fprintf(outfile, buf);
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
** 語法規則#5(改) <IntDeclaration>
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
        sprintf(buf, "\t%s\tDW\t", token->value);
        fprintf(outfile, buf);
        token = nextToken();
    }
	if (token->sym == symBECOMES){
		token = nextToken();
		//Expression();
		if(token->sym == symNUMBER){
            sprintf(buf, "%s\n", token->value);
            fprintf(outfile, buf);
            token = nextToken();
        }
	}  
	else{
		sprintf(buf, "0\n");
		fprintf(outfile,buf);
  	}
	while (token->sym == symCOMMA){
		token = nextToken();
		if (token->sym == symIDENTIFIER){
	        if (checkexist()){
	        	Error(19);
			} 
	        idobj = newIdobj(token->value, token->sym, symINT, level);
	        idobjpush(idobj);
	        sprintf(buf, "\t%s\tDW\t", token->value);
        	fprintf(outfile, buf);
	        token = nextToken();
	    }
		if (token->sym == symBECOMES){
			token = nextToken();
			//Expression();
			if(token->sym == symNUMBER){
	            sprintf(buf, "%s\n", token->value);
	            fprintf(outfile, buf);
	            token = nextToken();
	        }
		}  
		else{
			sprintf(buf, "0\n");
			fprintf(outfile,buf);
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
** 語法規則#6(改) <VoidDeclaration>
*/
void VoidDeclaration(){
	int i=0;
	int tail;
	if (strcmp(token->value, "void")==0){
		token = nextToken();
		tail = 0;
		if (token->sym == symIDENTIFIER){
	        if (checkexist()){
	        	Error(20);
			} 
	        idobj = newIdobj(token->value, token->sym, symVOID, level);
	        idobjpush(idobj);
	        tail = ++labelCount;
	        sprintf(buf,"\tJMP\t_go%d\n%s:\n"
	                    "\tJMP\t_start%d\n",
	                    tail, token->value, labelCount);
	        fprintf(outfile,buf);
	        token = nextToken();
	    }
		if (token->sym == symLPAREN){
			token = nextToken();
			if (token->sym == symRPAREN){
				token = nextToken();
				sprintf(buf, "_start%d:\n", labelCount);
    			fprintf(outfile, buf);
    			++labelCount;
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
	sprintf(buf, "\tRET\n_go%d:\n"
				 "\tJMP\t_start%d\n",tail,labelCount);
	fprintf(outfile, buf);
}
/*
** 語法規則#7 <Statement>
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
** 語法規則#8 <AssignmentStatement>
*/
void AssignmentStatement(){
    char result[BUFSIZE];
    idobj=getIdobj(token->value);
    if (idobj != NULL){
      	sprintf(result, "%s", idobj->name);
    }
	Identifier();
	
    if (token->sym == symBECOMES){
    	token = nextToken();
    	/*
    	if (token->sym == symCHAR){
			sprintf(buf, "\tMOV\tWORD[%s], %s\n", result,token->value);
    		fprintf(outfile, buf);
		}
		else if(token->sym == symSTRING){
			sprintf(buf, "\tMOV\tWORD[%s], %s\n", result,token->value);
    		sprintf(outfile, buf);
		}
		*/
    	//else{
    		Expression();
	    	sprintf(buf, "\tPOP\tAX\n"
						 "\tMOV\t[%s], AX\n", result);
	        fprintf(outfile, buf);
		//}
    	
	}
	else if (token->sym == symLPAREN){
		sprintf(buf, "\tCALL\t%s\n", idobj);
        fprintf(outfile, buf);
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
** 語法規則#10 <CompoundStatement>
*/
void CompoundStatement(){
	
	int braces=0;//大括弧數量 
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
** 語法規則#11 <IfStatement>
*/
void IfStatement(){
	int head, tail;
    if (strcmp(token->value,"if")==0){
    	token = nextToken();
    	Condition();
    	head = labelCount;
        tail = ++labelCount;
        sprintf(buf, "\tJMP\t_go%d\n"
               		 "_go%d:\n", tail,head);
        fprintf(outfile, buf);
		CompoundStatement();
		sprintf(buf, "_go%d:\n", tail);
        fprintf(outfile, buf);
	}
    else{
    	Error(0);
    	skip(statement, 15);
	}
    
}
/*
** 語法規則#12 <WhileStatement>
*/
void WhileStatement(){
	int home, head, tail;
    if (strcmp(token->value,"while")==0){
    	token = nextToken();
    	home = ++labelCount;
        sprintf(buf, "_go%d:\n", home);
        fprintf(outfile, buf);
    	Condition();
    	head = labelCount;
        tail = ++labelCount;
        sprintf(buf, "\tJMP\t_go%d\n"
               "_go%d:\n", tail, head);
        fprintf(outfile, buf);
    	CompoundStatement();
    	sprintf(buf, "\tJMP\t_go%d\n", home);
        fprintf(outfile, buf);
	}
    else{
    	Error(0);
    	skip(statement, 15);
	}
	sprintf(buf, "_go%d:\n", tail);
    fprintf(outfile, buf);
    
}
/*
** 語法規則#13 <printfDeclaration>
*/
void PrintfDeclaration(){
	int printnum=0;//輸出變數的數量 
	int i=0;
	int box[5]={0,0,0,0,0};
	int boxnum=0;
	int boxnumtmp=0;
	
    if (strcmp(token->value,"printf")==0){
    	token = nextToken();
    	if(token->sym == symLPAREN){
    		token = nextToken();
    		if(token->sym == symSTRING){
    			for(i=0;i<strlen(token->value);i++){
    				if(token->value[i]=='%'){
    					if(token->value[i+1]=='d'){
    						printnum++;
    						box[boxnum]=1;
    						boxnum++;
						}
						if(token->value[i+1]=='c'||token->value[i+1]=='s'){
							printnum++;
							box[boxnum]=2;
    						boxnum++;
						}
						i++;
					}
					else if(token->value[i]=='\\'){
    					if(token->value[i+1]=='n'){
    						//sprintf(buf,"\tnewline\n");
                        	//fprintf(outfile,buf);
                        	box[boxnum]=3;
    						boxnum++;
						}
						i++;
					}
					else{
						sprintf(buf,"\tMOV\tword[_intstr], '%c$'\n"
									"\tMOV\tDX, _intstr\n"
			                        "\tMOV\tAH, 09H\n"
			                        "\tINT\t21H\n",token->value[i]);
		                fprintf(outfile, buf);
					}
				}
				
	    		token = nextToken();
	    		//while(printnum>0){
	    		
	    		while(boxnum>0){
	    			int tmp=0;
					if(box[boxnumtmp]==3){
						sprintf(buf,"\tnewline\n");
                		fprintf(outfile,buf);
					}
					
					else if(box[boxnumtmp]==1||box[boxnumtmp]==2){
						if(token->sym == symCOMMA){
							
			    			token = nextToken();
			    			if(box[boxnumtmp]==1){
			    				
								sprintf(buf, "\titostr\t%s, _intstr, '$'\n"
		                            		 "\tMOV\tDX, _intstr\n"
		                            		 "\tMOV\tAH, 09H\n"
		                            		 "\tINT\t21H\n", token->value);
		                    	fprintf(outfile, buf);
							}
		                    else if(box[boxnumtmp]==2){
		                    	
					            sprintf(buf,"\tMOV\tDX, %s\n"
					                        "\tMOV\tAH, 09H\n"
					                        "\tINT\t21H\n",token->value);
				                fprintf(outfile, buf);

							}
			    			if (token->sym == symIDENTIFIER){
			    				
								//token = nextToken();
								//sprintf(id, "%s_%s",idobj->procname, token->value);
								Identifier();
								
							}
							else{
								Error(5);
							}
						}
						else{
							Error(17);
						}
						
						
					}
					//printnum--;
					boxnumtmp++;
					boxnum--;
					
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
** 語法規則#15 <IdentifierList>
*/
void IdentifierList(){
    Identifier();
    while (token->sym == symCOMMA){
		token = nextToken();
		Identifier();
    }
}
/*
** 語法規則#16 <Condition>
*/
void Condition(){
	if (token->sym == symLPAREN){
    	token = nextToken();
    	Expression();
	    if (token->sym == symLESS ||token->sym == symLEQ ||token->sym == symEQ ||token->sym == symNEQ ||token->sym == symGREATER ||token->sym == symGEQ){
	    	int op = token->sym;
			token = nextToken();
	    	Expression();
	    	sprintf(buf, "\tPOP\tBX\n"
                   		 "\tPOP\tAX\n"
                   		 "\tCMP\tAX, BX\n");
      		fprintf(outfile, buf);
      		switch (op){
	            case symEQ:
	              sprintf(buf,"\tJE\t_go%d\n",(++labelCount));
	              fprintf(outfile, buf);
	              break;
	            case symNEQ:
	              sprintf(buf,"\tJNE\t_go%d\n",(++labelCount));
	              fprintf(outfile, buf);
	              break;
	            case symLESS:
	              sprintf(buf,"\tJL\t_go%d\n",(++labelCount));
	              fprintf(outfile, buf);
	              break;
	            case symLEQ:
	              sprintf(buf,"\tJLE\t_go%d\n",(++labelCount));
	              fprintf(outfile, buf);
	              break;
	            case symGREATER:
	              sprintf(buf,"\tJG\t_go%d\n",(++labelCount));
	              fprintf(outfile, buf);
	              break;
	            case symGEQ:
	              sprintf(buf,"\tJGE\t_go%d\n",(++labelCount));
	              fprintf(outfile, buf);
	              break;
	        }
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
** 語法規則#17 <Expression>
*/
void Expression(){
    if (token->sym == symPLUS ||token->sym == symMINUS){
    	token = nextToken();
	}
	Term();
    while (token->sym == symPLUS ||token->sym == symMINUS){
		int op = token->sym;
		token = nextToken();
		Term();
		if(op==symPLUS){
            fprintf(outfile,"\tPOP\tBX\n"
							"\tPOP\tAX\n"
                    		"\tADD\tAX, BX\n"
                    		"\tPUSH\tAX\n");
        }
        else{
            fprintf(outfile, "\tPOP\tBX\n"
                			 "\tPOP\tAX\n"
                     		 "\tSUB\tAX, BX\n"
                    		 "\tPUSH\tAX\n");
        }
	}
}
/*
** 語法規則#18 <Term>
*/
void Term(){
    Factor();
    while (token->sym == symMUL ||token->sym == symDIV ||token->sym == symDIVREM){
		int op = token->sym;
		token = nextToken();
		Factor();
		if(op==symMUL){
            fprintf(outfile, "\tPOP\tBX\n"
                    		 "\tPOP\tAX\n"
                   			 "\tMUL\tBX\n"
                    		 "\tPUSH\tAX\n");
        }
        else if(op==symDIV){
            fprintf(outfile, "\tPOP\tBX\n"
                     		 "\tMOV\tDX, 0\n"
                    		 "\tPOP\tAX\n"
                    		 "\tDIV\tBX\n"
                    		 "\tPUSH\tAX\n");
        }
        else if(op==symDIVREM){
            fprintf(outfile, "\tPOP\tBX\n"
                     		 "\tMOV\tDX, 0\n"
                    		 "\tPOP\tAX\n"
                    		 "\tDIV\tBX\n"
                    		 "\tPUSH\tDX\n");
        }
    }
}
/*
** 語法規則#19 <Factor>
*/
void Factor(){
    if (token->sym == symIDENTIFIER){
    	sprintf(buf,"\tPUSH\tWORD [%s]\n",token->value);
      	fprintf(outfile, buf);
		Identifier();
	}
    else if (token->sym == symNUMBER){
    	sprintf(buf, "\tPUSH\t%s\n", token->value);
        fprintf(outfile, buf);
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
** 識別字符記處理
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
** 數字符記處理
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
************************** 主程式 **********************
*/
int main(int argc, char *argv[]){
	char openfile[20]="";
	printf("請輸入要執行的檔名：\n");
	scanf("%s",&openfile);
    FILE *f=fopen(openfile, "r");
    
    //strcpy(openfile,"test_8.c");
    //FILE *f=fopen(openfile, "r");
    
    int nn=strlen(openfile);
    strncpy(progname, openfile, nn-2);
    strcpy(outname, progname);
    
    scanner(f);
    followsyminit();
    token = nextToken();
    Program();
    
    
    fprintf(outfile, "\tMOV\tAX, 4C00H\n"
					 "\tINT\t21H\n");
    printf("\n  Plone compile completed.\n  Error count : %d\n", errorCount);
    if (argc==3){
		printf("\n識別字結構堆疊內容如下：\n%s\n", idobjstackToString());
	}
	fclose(outfile);
    fclose(f);
    if (errorCount==0){
		FILE *batchfile;
		sprintf(buf, "%s.bat", progname);
		batchfile=fopen(buf,"w");
		fprintf(batchfile, "nasmw %s.asm -o %s.com\n",progname, progname);
		fprintf(batchfile, "%s.com\n", progname);
		fclose(batchfile);
	}
    return 0;
}

//nasmw test??.asm -o test??.com
