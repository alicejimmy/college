#include <iostream>
#include <string>
#include <windows.h>
#ifndef CARD_H
#define CARD_H
using namespace std;

class card {
public:
	string suits();//return suits 
	int number();//return num
	string printtypeone(int);
	string printtypeonexy(int, int, int);

	void suitnum(int);
	void num(int);
	void typeone(int);
	void setcolor(int);
	void randomcard(int);
	void cardinorder();
	void setcardsuitnum(int, int, int);
	void gotoxy(int, int);
	void getplayerscard();
	void seven(int);
	void checkcard(int);
	void cardplayed(int);

private:
	string Suits;
	int Num;
	string Card;
	string cardpicone[11][19];
	int order[55];
	int playerone[27],playertwo[27];
	int cardtable[4][5];//�X�b��W���P
	int howcard;//�P�ण��X

};
#endif#pragma once
