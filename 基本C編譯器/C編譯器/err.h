/************************ err.h **********************/
#define ERRMAX 22
char errmsgs[ERRMAX][36]=
{
  "未知寫法",           	    /*errmsgs[0] */
  "未引入函式庫",               /*errmsgs[1] */
  "遺漏include",                /*errmsgs[2] */
  "遺漏<>",                     /*errmsgs[3] */
  "未知函式庫",                 /*errmsgs[4] */
  "遺漏識別字",                 /*errmsgs[5] */
  "遺漏[]",                     /*errmsgs[6] */
  "遺漏數字",                   /*errmsgs[7] */
  "超出陣列數量",               /*errmsgs[8] */
  "遺漏;",                      /*errmsgs[9] */
  "遺漏)",                      /*errmsgs[10]*/
  "遺漏(",                      /*errmsgs[11]*/
  "遺漏{",                      /*errmsgs[12]*/
  "遺漏}",                      /*errmsgs[13]*/
  "關係運算子錯誤",             /*errmsgs[14]*/
  "飛越至下一個敘述",           /*errmsgs[15]*/
  "遺漏雙引號",                 /*errmsgs[16]*/
  "遺漏,",                      /*errmsgs[17]*/
  "char宣告常數重複",           /*errmsgs[18]*/
  "int宣告變數重複",            /*errmsgs[19]*/
  "void宣告變數重複",           /*errmsgs[20]*/
  "識別字沒有宣告",             /*errmsgs[21]*/
  //"遺漏數字",                   /*errmsgs[22]*/
  //"飛越至下一個敘述",           /*errmsgs[23]*/
  //"CONST宣告常數重複",          /*errmsgs[24]*/
  //"VAR宣告變數重複",            /*errmsgs[25]*/
  //"識別字沒有宣告"              /*errmsgs[26]*/
  //"識別字沒有宣告"              /*errmsgs[26]*/
};
