/************* sym.h **************/
#define symSYMMAX         32//44

#define symEOF             0
#define symerror           1//1  錯誤(沒出現在以下的語法)
#define symIDENTIFIER      2//2  變數(英文a到z或A到Z組合而成)
#define symNUMBER          3//3  數字(0到9組合而成)
#define symPLUS            4//4  加號+
#define symMINUS           5//5  減號-
#define symMUL             6//6  乘號*
#define symDIV             7//7  除號/
#define symEQ              8//8  等於==
#define symNEQ             9//9  不等於!=
#define symLESS           10//10 小於<
#define symLEQ            11//11 小於等於<=
#define symGREATER        12//12 大於>
#define symGEQ            13//13 大於等於>=
#define symLPAREN         14//14 左括號(
#define symRPAREN         15//15 右括號)
#define symCOMMA          16//16 逗號,
#define symSEMI           17//17 分號；
#define symPERIOD         18//18 句號.
#define symBECOMES        19//19 為=
//#define symBEGIN          20
//#define symEND            21
//#define symIF             22
//#define symTHEN           23
//#define symWHILE          24
//#define symDO             25
//#define symREAD           26
//#define symWRITE          27
//#define symIDENTIFIERLIST 28
//#define symCALL           29

#define symNOT            20//28 否!
#define symHASHTAG        21//29 井字號# 

//#define symCONST          30
//#define symVAR            31
//#define symPROCEDURE      32
//#define symPROGRAM        33

#define symLBRACKE        22//31 左中括號[ 
#define symRBRACKE        23//32 右中括號] 
//#define symMAIN           33

//#define symSTRINGINSIDE   24//34
#define symSTRING   24//34 字串內容(""裡面的內容)

#define symLBRACES        25//35 左大括號{
#define symRBRACES        26//36 右大括號}
#define symDIVREM         27//37 除餘數%
#define symCHAR           28//(新加) 字元內容(''裡面的內容) 
#define symchar           29//38
#define symINT            30//39
//#define symPRINTF         40
//#define symFLOAT          41
//#define symSTRING         42
#define symVOID           31//43


