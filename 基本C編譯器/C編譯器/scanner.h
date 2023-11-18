/********************** scanner.h ********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym.h"
#include "symbol.h"

int nextChar;
int cp = 0;
int linelen = 0;
int linenum = 0;
char line[512];
FILE *sourcefile;
void advance() {
	cp++;
	if (cp < linelen) {
    	nextChar = line[cp];
    }
  	else {
    	if (feof(sourcefile)) {
			linelen = 0;
			nextChar = -1;
    	}
	    else {
	    	if (fgets(line, 512, sourcefile) != NULL) {
		        linelen = strlen(line);
		        linenum++;
		        cp = 0;
		        nextChar = line[cp];
		        printf("%4d %s", linenum, line);
	      	}
    	}
  	}
}

struct symbolTag *nextToken() {
	static char s[128] = "";
	int n=0;
	int sqm=39;//單引號
	char SQM=sqm;
	while (1) {
		memset(s, 0, 128);
    	if (nextChar>='a' && nextChar<='z' || nextChar>='A' && nextChar<='Z') {
      		do {
		        s[n++]=nextChar;
		        advance();
      		} while (nextChar >= 'a' && nextChar <= 'z' || nextChar >= 'A' && nextChar <= 'Z' || nextChar>='0' && nextChar<='9');
			s[n] = '\0';
			return newSymbol(symIDENTIFIER, linenum, cp, s);
			/*
			if (!strcmp(s, "begin")) {
				s[n] = '\0';
				return newSymbol(symBEGIN, linenum, cp, s);
			}
			else if (!strcmp(s, "end")) {
				s[n] = '\0';
				return newSymbol(symEND, linenum, cp, s);
			}
			else if (!strcmp(s, "if")) {
				s[n] = '\0';
				return newSymbol(symIF, linenum, cp, s);
			}
			else if (!strcmp(s, "then")) {
				s[n] = '\0';
				return newSymbol(symTHEN, linenum, cp, s);
			}
			else if (!strcmp(s, "while")) {
				s[n] = '\0';
				return newSymbol(symWHILE, linenum, cp, s);
			}
			else if (!strcmp(s, "do")) {
				s[n] = '\0';
				return newSymbol(symDO, linenum, cp, s);
			}
			else if (!strcmp(s, "read")) {
				s[n] = '\0';
				return newSymbol(symREAD, linenum, cp, s);
			}
			else if (!strcmp(s, "write")) {
				s[n] = '\0';
				return newSymbol(symWRITE, linenum, cp, s);
			}
			else if (!strcmp(s, "const")) {
				s[n] = '\0';
				return newSymbol(symCONST, linenum, cp, s);
			}
			else if (!strcmp(s, "char")) {
				
				s[n] = '\0';
				return newSymbol(symCHAR, linenum, cp, s);
			}
			else if (!strcmp(s, "int")) {
				s[n] = '\0';
				return newSymbol(symINT, linenum, cp, s);
			}
			else if (!strcmp(s, "printf")) {
				s[n] = '\0';
				return newSymbol(symPRINTF, linenum, cp, s);
			}
			else if (!strcmp(s, "float")) {
				s[n] = '\0';
				return newSymbol(symFLOAT, linenum, cp, s);
			}
			else if (!strcmp(s, "string")) {
				s[n] = '\0';
				return newSymbol(symSTRING, linenum, cp, s);
			}
			else if (!strcmp(s, "void")) {
				s[n] = '\0';
				return newSymbol(symVOID, linenum, cp, s);
			}
			else if (!strcmp(s, "main")) {
				s[n] = '\0';
				return newSymbol(symMAIN, linenum, cp, s);
			}
			else {
				s[n] = '\0';
				return newSymbol(symIDENTIFIER, linenum, cp, s);
			}
			*/
    	}
    	else if (nextChar>='0' && nextChar<='9') {
      		do {
		        s[n++]=nextChar;
		        advance();
      		} while (nextChar >= '0' && nextChar <= '9');
			s[n] = '\0';
      		return newSymbol(symNUMBER,linenum,cp,s);
    	}
    	else {
    		if(nextChar==SQM){
    			advance();
					while (nextChar!=SQM) {
						s[n++]=nextChar;
						advance();
					}
					advance();
					s[n]='\0';
					return newSymbol(symCHAR, linenum, cp, s);
			}
      		switch (nextChar) {
				case ';':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symSEMI,linenum,cp,s);
				case '.':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symPERIOD,linenum,cp,s);
				case ',':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symCOMMA,linenum,cp,s);
				case '(':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symLPAREN,linenum,cp, s);
				case ')':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symRPAREN,linenum,cp, s);
				case '+':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symPLUS,linenum,cp,s);
				case '-':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symMINUS,linenum,cp, s);
				case '*':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symMUL,linenum,cp, s);
				case '/':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symDIV,linenum,cp, s);
				case '=':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					if (nextChar == '=') {
						s[n++] = nextChar;
						advance();
						s[n] = '\0';
						return newSymbol(symEQ, linenum, cp, s);
					}
					else {
						return newSymbol(symBECOMES, linenum, cp, s);
					}
				case '<':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					if (nextChar=='=') {
						s[n++]=nextChar;
						advance();
						s[n]='\0';
						return newSymbol(symLEQ,linenum,cp,s);
					}
					else {
						return newSymbol(symLESS,linenum,cp,s);
					}
				case '>':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					if (nextChar=='=') {
						s[n++]=nextChar;
						advance();
						s[n]='\0';
						return newSymbol(symGEQ,linenum,cp,s);
					}
					else{
						return newSymbol(symGREATER,linenum,cp,s);
					}
				/*
				case ':':
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					if (nextChar=='=') {
						s[n++]=nextChar;
						advance();
						s[n]='\0';
						return newSymbol(symBECOMES,linenum,cp, s);
					}
					else {
						return newSymbol(symerror,linenum,cp, s);
					}
				*/
				case '"':
					advance();
					while (nextChar!='"') {
						s[n++]=nextChar;
						advance();
					}
					advance();
					s[n]='\0';
					//return newSymbol(symSTRINGINSIDE,linenum,cp,s);
					return newSymbol(symSTRING, linenum, cp, s);
				/*
				case ''':
					advance();
					while (nextChar!="'") {
						s[n++]=nextChar;
						advance();
					}
					advance();
					s[n]='\0';
					return newSymbol(symCHAR, linenum, cp, s);
				*/
				case '{':
					s[n++] = nextChar;
					s[n] = '\0';
					advance();
					return newSymbol(symLBRACES, linenum, cp, s);
				case '}':
					s[n++] = nextChar;
					s[n] = '\0';
					advance();
					return newSymbol(symRBRACES, linenum, cp, s);
				case '%':
					s[n++] = nextChar;
					s[n] = '\0';
					advance();
					return newSymbol(symDIVREM, linenum, cp, s);
				case '!':
					s[n++] = nextChar;
					s[n] = '\0';
					advance();
					if (nextChar == '=') {
						s[n++] = nextChar;
						advance();
						s[n] = '\0';
						return newSymbol(symNEQ, linenum, cp, s);
					}
					else {
						return newSymbol(symNOT, linenum, cp, s);
					}
				case '#':
					s[n++] = nextChar;
					s[n] = '\0';
					advance();
					return newSymbol(symHASHTAG, linenum, cp, s);
				case '[':
					s[n++] = nextChar;
					s[n] = '\0';
					advance();
					return newSymbol(symLBRACKE, linenum, cp, s);
				case ']':
					s[n++] = nextChar;
					s[n] = '\0';
					advance();
					return newSymbol(symRBRACKE, linenum, cp, s);

				case '\0':
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					advance();          //忽略空白字元
					break;
				case -1:
					return NULL;
				default:
					s[n++]=nextChar;
					s[n]='\0';
					advance();
					return newSymbol(symerror, linenum,cp,s);
      		}
    	}
  	}
}

void scanner(FILE *f) {
	sourcefile = f;
}
