/******************** symname.h *******************/
#include <stdlib.h>
#include "sym.h"
char names[symSYMMAX][32];
void symnameinit() {
	strcpy(names[symEOF],"EOF");
	strcpy(names[symerror],"error");
	strcpy(names[symIDENTIFIER],"IDENTIFIER");
	strcpy(names[symNUMBER],"NUMBER");
	strcpy(names[symPLUS],"PLUS");
	strcpy(names[symMINUS],"MINUS");
	strcpy(names[symMUL],"MUL");
	strcpy(names[symDIV],"DIV");
	strcpy(names[symEQ],"EQ");
	strcpy(names[symNEQ],"NEQ");
	strcpy(names[symLESS],"LESS");
	strcpy(names[symLEQ],"LEQ");
	strcpy(names[symGREATER],"GREATER");
	strcpy(names[symGEQ],"GEQ");
	strcpy(names[symLPAREN],"LPAREN");
	strcpy(names[symRPAREN],"RPAREN");
	strcpy(names[symCOMMA],"COMMA");
	strcpy(names[symSEMI],"SEMI");
	strcpy(names[symPERIOD],"PERIOD");
	strcpy(names[symBECOMES],"BECOMES");
	/*
	strcpy(names[symBEGIN],"BEGIN");
	strcpy(names[symEND],"END");
	strcpy(names[symIF],"IF");
	strcpy(names[symTHEN],"THEN");
	strcpy(names[symWHILE],"WHILE");
	strcpy(names[symDO],"DO");
	strcpy(names[symREAD],"READ");
	strcpy(names[symWRITE],"WRITE");
	*/
	//strcpy(names[symIDENTIFIERLIST],"IDENTIFIERLIST");
	//strcpy(names[symCALL],"CALL");
	
	strcpy(names[symNOT], "NOT");
	strcpy(names[symHASHTAG], "HASHTAG");
	/*
	strcpy(names[symCONST],"CONST");
	*/
	//strcpy(names[symVAR],"VAR");
	//strcpy(names[symPROCEDURE],"PROCEDURE");
	//strcpy(names[symPROGRAM],"PROGRAM");

	strcpy(names[symLBRACKE], "LBRACKE");
	strcpy(names[symRBRACKE], "RBRACKE");
	/*
	strcpy(names[symMAIN], "MAIN");
	*/

	//strcpy(names[symSTRINGINSIDE],"STRINGINSIDE");
	strcpy(names[symSTRING], "STRING");

	strcpy(names[symLBRACES], "LBRACES");
	strcpy(names[symRBRACES], "RBRACES");
	strcpy(names[symDIVREM], "DIVREM");
	/*
	strcpy(names[symCHAR], "CHAR");
	strcpy(names[symINT], "INT");
	strcpy(names[symPRINTF], "PRINTF");
	strcpy(names[symFLOAT], "FLOAT");
	strcpy(names[symSTRING], "STRING");
	strcpy(names[symVOID], "VOID");
	*/
}
