#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "card.h"
using namespace std;

string card::suits() {
	return Suits;
}

int card::number() {
	return Num;
}

string card::printtypeone(int suitnum) {
	int i, j;
	card card2;
	cout << " ";
	card2.setcolor(249);
	cout << "                   " << endl;
	card2.setcolor(7);
	cout << " ";
	card2.setcolor(249);
	if (Num == 0) {
		cout << "                   ";
	}
	else if (Num == 1) {
		cout << "  A                ";
	}
	else if (2 <= Num && Num <= 9) {
		cout << "  " << Num << "                ";
	}
	else if (Num == 10) {
		cout << "  " << Num << "               ";
	}
	else if (Num == 11) {
		cout << "  J                ";
	}
	else if (Num == 12) {
		cout << "  Q                ";
	}
	else if (Num == 13) {
		cout << "  K                ";
	}
	card2.setcolor(7);
	cout << " " << endl;
	for (i = 0; i <= 10; i++) {
		card2.setcolor(7);
		cout << " ";
		card2.setcolor(249);
		cout << " ";
		if (suitnum == 1 || suitnum == 2) {
			card2.setcolor(252);
		}
		else if (suitnum == 3 || suitnum == 4 || suitnum == 5) {
			card2.setcolor(240);
		}
		for (j = 0; j <= 16; j++) {
			cout << cardpicone[i][j];
		}
		card2.setcolor(240);
		cout << " " << endl;
	}
	card2.setcolor(7);
	cout << " ";
	card2.setcolor(249);
	if (Num == 0) {
		cout << "                   ";
	}
	else if (Num == 1) {
		cout << "                A  ";
	}
	else if (2 <= Num && Num <= 9) {
		cout << "                " << Num << "  ";
	}
	else if (Num == 10) {
		cout << "               " << Num << "  ";
	}
	else if (Num == 11) {
		cout << "                J  ";
	}
	else if (Num == 12) {
		cout << "                Q  ";
	}
	else if (Num == 13) {
		cout << "                K  ";
	}

	cout << endl;
	card2.setcolor(7);
	cout << " ";
	card2.setcolor(249);
	cout << "                   " << endl;
	return Card;
}

string card::printtypeonexy(int suitnum, int x, int y) {
	int i, j;
	card card2;
	gotoxy(x, y);
	cout << " ";
	card2.setcolor(249);
	cout << "                   " << endl;
	y++;
	gotoxy(x, y);
	card2.setcolor(7);
	cout << " ";
	card2.setcolor(249);
	if (Num == 0) {
		cout << "                   ";
	}
	else if (Num == 1) {
		cout << "  A                ";
	}
	else if (2 <= Num && Num <= 9) {
		cout << "  " << Num << "                ";
	}
	else if (Num == 10) {
		cout << "  " << Num << "               ";
	}
	else if (Num == 11) {
		cout << "  J                ";
	}
	else if (Num == 12) {
		cout << "  Q                ";
	}
	else if (Num == 13) {
		cout << "  K                ";
	}
	card2.setcolor(7);
	cout << " " << endl;
	for (i = 0; i <= 10; i++) {
		y++;
		gotoxy(x, y);
		card2.setcolor(7);
		cout << " ";
		card2.setcolor(249);
		cout << " ";
		if (suitnum == 1 || suitnum == 2) {
			card2.setcolor(252);
		}
		else if (suitnum == 3 || suitnum == 4 || suitnum == 5) {
			card2.setcolor(240);
		}
		for (j = 0; j <= 16; j++) {
			cout << cardpicone[i][j];
		}
		card2.setcolor(240);
		cout << " " << endl;
	}
	y++;
	gotoxy(x, y);
	card2.setcolor(7);
	cout << " ";
	card2.setcolor(249);
	if (Num == 0) {
		cout << "                   ";
	}
	else if (Num == 1) {
		cout << "                A  ";
	}
	else if (2 <= Num && Num <= 9) {
		cout << "                " << Num << "  ";
	}
	else if (Num == 10) {
		cout << "               " << Num << "  ";
	}
	else if (Num == 11) {
		cout << "                J  ";
	}
	else if (Num == 12) {
		cout << "                Q  ";
	}
	else if (Num == 13) {
		cout << "                K  ";
	}

	cout << endl;
	y++;
	gotoxy(x, y);
	card2.setcolor(7);
	cout << " ";
	card2.setcolor(249);
	cout << "                   " << endl;
	return Card;
}

void card::suitnum(int suitnum) {
	if (suitnum == 1) {
		Suits = "diamond";
	}
	else if (suitnum == 2) {
		Suits = "heart";
	}
	else if (suitnum == 3) {
		Suits = "spade";
	}
	else if (suitnum == 4) {
		Suits = "club";
	}
	else if (suitnum == 5) {
		Suits = "joker";
		Num = 0;
	}
}

void card::num(int num) {
	Num = num;
}

void card::typeone(int suitnum) {
	int i = 0;
	cardpicone[0][i++] = { "                 " };
	i = 0;
	if (suitnum == 1) {
		cardpicone[1][i++] = "        *        ";
		i = 0;
		cardpicone[2][i++] = "       ***       ";
		i = 0;
		cardpicone[3][i++] = "     *******     ";
		i = 0;
		cardpicone[4][i++] = "   ***********   ";
		i = 0;
		cardpicone[5][i++] = " *************** ";
		i = 0;
		cardpicone[6][i++] = "   ***********   ";
		i = 0;
		cardpicone[7][i++] = "     *******     ";
		i = 0;
		cardpicone[8][i++] = "       ***       ";
		i = 0;
		cardpicone[9][i++] = "        *        ";
		i = 0;
	}
	else if (suitnum == 2) {
		cardpicone[1][i++] = "  *****   *****  ";
		i = 0;
		cardpicone[2][i++] = " ******* ******* ";
		i = 0;
		cardpicone[3][i++] = " *************** ";
		i = 0;
		cardpicone[4][i++] = " *************** ";
		i = 0;
		cardpicone[5][i++] = "  *************  ";
		i = 0;
		cardpicone[6][i++] = "    *********    ";
		i = 0;
		cardpicone[7][i++] = "      *****      ";
		i = 0;
		cardpicone[8][i++] = "       ***       ";
		i = 0;
		cardpicone[9][i++] = "        *        ";
		i = 0;
	}
	else if (suitnum == 3) {
		cardpicone[1][i++] = "        *        ";
		i = 0;
		cardpicone[2][i++] = "      *****      ";
		i = 0;
		cardpicone[3][i++] = "     *******     ";
		i = 0;
		cardpicone[4][i++] = "   ***********   ";
		i = 0;
		cardpicone[5][i++] = " *************** ";
		i = 0;
		cardpicone[6][i++] = " *************** ";
		i = 0;
		cardpicone[7][i++] = "  *************  ";
		i = 0;
		cardpicone[8][i++] = "        *        ";
		i = 0;
		cardpicone[9][i++] = "       ***       ";
		i = 0;
	}
	else if (suitnum == 4) {
		cardpicone[1][i++] = "       ***       ";
		i = 0;
		cardpicone[2][i++] = "      *****      ";
		i = 0;
		cardpicone[3][i++] = "      *****      ";
		i = 0;
		cardpicone[4][i++] = "   **  ***  **   ";
		i = 0;
		cardpicone[5][i++] = " *************** ";
		i = 0;
		cardpicone[6][i++] = " *************** ";
		i = 0;
		cardpicone[7][i++] = "   **  ***  **   ";
		i = 0;
		cardpicone[8][i++] = "        *        ";
		i = 0;
		cardpicone[9][i++] = "       ***       ";
		i = 0;
	}
	else if (suitnum == 5) {

		cardpicone[1][i++] = " J               ";
		i = 0;
		cardpicone[2][i++] = " O               ";
		i = 0;
		cardpicone[3][i++] = " K               ";
		i = 0;
		cardpicone[4][i++] = " E               ";
		i = 0;
		cardpicone[5][i++] = " R             J ";
		i = 0;
		cardpicone[6][i++] = "               O ";
		i = 0;
		cardpicone[7][i++] = "               K ";
		i = 0;
		cardpicone[8][i++] = "               E ";
		i = 0;
		cardpicone[9][i++] = "               R ";
		i = 0;
	}
	cardpicone[10][i++] = { "                 " };
}

void card::setcolor(int ForeColor) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

void card::randomcard(int num) {
	int n, tmp;
	srand((unsigned)time(NULL));
	for (int i = 1; i <= num; i++) {
		n = rand() % num + 1;
		tmp = order[i];
		order[i] = order[n];
		order[n] = tmp;
	}
}
void card::cardinorder() {
	for (int j = 1; j <= 54; j++) {
		order[j] = j;
	}
}

void card::setcardsuitnum(int NO, int x, int y) {
	int cardsuit, cardnum;
	cardsuit = (order[NO] / 13) + 1;
	if (order[NO] % 13 == 0) {
		cardsuit--;
	}
	suitnum(cardsuit);
	if (cardsuit == 1 || cardsuit == 2 || cardsuit == 3 || cardsuit == 4) {
		cardnum = order[NO] % 13;
		if (cardnum == 0) {
			cardnum = 13;
		}
		num(cardnum);
	}
	typeone(cardsuit);
	cout << printtypeonexy(cardsuit, x, y);
	setcolor(7);
	cout << endl;
}

void card::gotoxy(int xpos, int ypos) {
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void card::getplayerscard() {
	int tmp = 0;
	for (int i = 1; i < 27; i++) {
		playerone[i] = order[i];
		playertwo[i] = order[i + 26];
	}
	for (int i = 1; i < 27; i++) {
		for (int j = i+1; j < 27; j++) {
			if (playerone[i] > playerone[j]) {
				tmp = playerone[i];
				playerone[i] = playerone[j];
				playerone[j] = tmp;
			}
		}
	}
	for (int i = 1; i < 27; i++) {
		int cardsuit, cardnum;
		cardsuit = (playerone[i] / 13) + 1;
		if (playerone[i] % 13 == 0) {
			cardsuit--;
		}
		suitnum(cardsuit);
		if (cardsuit == 1 || cardsuit == 2 || cardsuit == 3 || cardsuit == 4) {
			cardnum = playerone[i] % 13;
			if (cardnum == 0) {
				cardnum = 13;
			}
			num(cardnum);
		}
		cout << Suits << " ";
		if (Num == 1) {
			cout << "A  ";
		}
		else if (2 <= Num && Num <= 10) {
			cout << Num << "  ";
		}
		else if (Num == 11) {
			cout << "J  ";
		}
		else if (Num == 12) {
			cout << "Q  ";
		}
		else if (Num == 13) {
			cout << "K  ";
		}
		if (i == 6 || i == 16) {
			cout << endl;
		}
	}
	cout << endl;
}
void card::seven(int d) {
	int whoturn = 0, end = 1, cardsuit = 0, cardnum = 0, mode, p = 1, ontable[53] = { 0 }, trashone = 0, trashtwo = 0, h = 26;
	//whoturn 1輪到玩家 2輪到電腦,end 1重複執行 0遊戲結束,p整場第幾張牌 跑ontable用,ontable出過的牌
	//trashone當前玩家累積積分,trashtwo當前電腦累積積分,h目前電腦有幾張牌,comcard 1可以出牌 2只能蓋牌
	for (int i = 1; i < 27; i++) {
		if (playerone[i] == 33) {
			whoturn = 1;
			cout << "It's your turn." << endl;
		}
		else if (playertwo[i] == 33) {
			whoturn = 2;
			cout << "It's conputer's turn." << endl;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == 1) {
				cardtable[i][j] = 20;
			}
			else if (j == 2) {
				cardtable[i][j] = 33;
			}
			else if (j == 3) {
				cardtable[i][j] = 7;
			}
			else if (j == 4) {
				cardtable[i][j] = 46;
			}
			if (i == 2) {
				cardtable[i][j] = 0;
			}
		}
	}
	while (end == 1) {
		int n, g, t = 0, k = 0;//n牌的代號,g隨機挑電腦的牌,t狀況分析,k儲存牌在玩家牌組裡為第幾張
		howcard = 0;
		if (whoturn == 1) {
			t = 0;
			n = 0;
			cout << endl << "Choose the card.(ex:spade7 enter 3 7;diamond K enter 1 13)(1:diamond 2:heart 3:spade 4:clubs)(A,J,Q,K please enter 1,11,12,13)" << endl;
			cin >> cardsuit >> cardnum;
			if (0 > cardsuit || cardsuit > 4) {
				cout << "Wrong enter." << endl << endl;
				continue;
			}
			if (0 > cardnum || cardnum > 13) {
				cout << "Wrong enter." << endl << endl;
				continue;
			}
			n = (cardsuit - 1) * 13 + cardnum;
			for (int i = 1; i < 27; i++) {
				if (n == playerone[i]) {
					k = i;
					t = 1;//牌是玩家的
				}
			}
			for (int i = 1; i < p; i++) {
				if (n == ontable[i]) {
					t = 3;//牌已經出過
				}
			}
			if (t == 0) {//牌是電腦的
				cout << "You can't steal computer's card." << endl;
				continue;
			}
			else if (t == 1) {//牌是玩家的
				for (int i = 1; i < 27; i++) {
					if (playerone[i] == 33) {
						if (n != 33) {//有黑桃7要先出
							cout << "You have spade7 ,you should play it first." << endl;
							t = 2;
							break;
						}
					}
					else if (playerone[i] == 7 || playerone[i] == 20 || playerone[i] == 46) {//有其他7要先出
						if (n == 33) {
							break;
						}
						else if (n != 7 && n != 20 && n != 46) {
							cout << "You have 7,you should play it first." << endl;
							t = 2;
							break;
						}
					}
				}
			}
			if (t == 2) {//有7要先出
				continue;
			}
			if (t == 3) {//牌已經出過
				cout << "This card had been played." << endl;
				continue;
			}
			suitnum(cardsuit);
			cout << endl << "You choose " << Suits;
			if (cardnum == 1) {
				cout <<" A.";
			}
			else if (2 <= cardnum && cardnum <= 10) {
				cout <<" "<< cardnum << ".";
			}
			else if (cardnum == 11) {
				cout << " J.";
			}
			else if (cardnum == 12) {
				cout << " Q.";
			}
			else if (cardnum == 13) {
				cout << " K.";
			}
			checkcard(n);
			cout <<endl<< "What do you want to do ? (1:Play出牌 2:Fold覆蓋牌 0:go back回到上一步)" << endl;
			cin >> mode;
			if (0 > mode || mode > 2) {
				cout << "Wrong enter." << endl << endl;
				continue;
			}
			else if (mode == 0) {
				continue;
			}
			else if (howcard == 1 && mode == 1) {
				ontable[p] = playerone[k];
				p++;
				playerone[k] = 0;
				cardplayed(n);
			}
			else if (howcard == 2 && mode == 1) {
				cout << "This card can only fold."<<endl;
				continue;
			}
			else if (howcard == 1 && mode == 2) {
				cout << "This card can only play."<<endl;
				continue;
			}
			else if (howcard == 2 && mode == 2) {
				trashone += playerone[k] % 13;
				if (playerone[k] % 13 == 0) {
					trashone += 13;
				}
				ontable[p] = playerone[k];
				p++;
				playerone[k] = 0;
			}
			if (mode == 1 || mode == 2) {
				if (p < 53) {
					cout << endl << "The cards you have is ";
				}
				int f;
				f = 0;//目前有幾張牌
				for (int i = 1; i < 27; i++) {
					if (playerone[i] != 0) {
						int suit, nums;
						suit = (playerone[i] / 13) + 1;
						if (playerone[i] % 13 == 0) {
							suit--;
						}
						suitnum(suit);
						if (suit == 1 || suit == 2 || suit == 3 || suit == 4) {
							nums = playerone[i] % 13;
							if (nums == 0) {
								nums = 13;
							}
						}
						cout << Suits << " ";
						if (nums == 1) {
							cout << "A  ";
						}
						else if (2<=nums&&nums<=10) {
							cout <<nums<< "  ";
						}
						else if (nums == 11) {
							cout << "J  ";
						}
						else if (nums == 12) {
							cout << "Q  ";
						}
						else if (nums == 13) {
							cout << "K  ";
						}
						f++;
						if (f == 6 || f == 16) {
							cout << endl;
						}
					}
				}
				cout << endl<<endl;
				cout << "You still have " << f << " card";
				if (f != 1) {
					cout << "s";
				}
				cout << "." << endl;
				cout << "And your points is " << trashone << "." << endl<<endl;
			}
		}
		else if (whoturn == 2) {
			int s, m;//s電腦所選牌的花色代碼,m電腦所選牌的號碼
			t = 0;//電腦有其他7
			n = 0;
			for (int i = 1; i < 27; i++) {
				if (playertwo[i] == 33) {
					t = 2;//電腦有黑桃7
					g = i;
					n = playertwo[i];
					break;
				}
			}
			if (t == 0) {
				for (int i = 1; i < 27; i++) {
					if (playertwo[i] == 7) {
						t = 0;
						g = i;
						n = playertwo[i];
						break;
					}
					else if (playertwo[i] == 20) {
						t = 0;
						g = i;
						n = playertwo[i];
						break;
					}
					else if (playertwo[i] == 46) {
						t = 0;
						g = i;
						n = playertwo[i];
						break;
					}
					else {
						t = 1;//電腦的牌組沒有7
					}
				}
			}
			if (d == 1) {
				if (t == 1) {//電腦的牌組沒有7
					for (int i = 1; i < h + 1; i++) {
						checkcard(playertwo[i]);
						if (howcard == 1) {
							g = i;
							n= playertwo[g];
							break;
						}
					}
					if (howcard == 2) {
						srand((unsigned)time(NULL));
						g = rand() % h + 1;
						n = playertwo[g];
					}
				}
				s = (n / 13) + 1;
				if (n % 13 == 0) {
					s--;
				}
				suitnum(s);
				m = n % 13;
				if (n % 13 == 0) {
					m = 13;
				}
				checkcard(n);
				if (howcard == 1) {
					ontable[p] = playertwo[g];
					p++;
					playertwo[g] = 0;
					cout << "Computer played " << Suits << " " << m << "." << endl;
					cardplayed(n);
				}
				else if (howcard == 2) {
					trashtwo += playertwo[g] % 13;
					if (playertwo[g] % 13 == 0) {
						trashtwo += 13;
					}
					ontable[p] = playertwo[g];
					p++;
					playertwo[g] = 0;
					cout << "Computer covered the card." << endl;
				}
				h--;
				for (int i = 1; i <= h; i++) {
					if (playertwo[i] == 0) {
						playertwo[i] = playertwo[h + 1];
						playertwo[h + 1] = 0;
					}
				}
				cout << "Computer still have " << h << " card";
				if (h != 1) {
					cout << "s";
				}
				cout << "." << endl;
				cout << "And computer's points is " << trashtwo << "." << endl << endl;
			}
		}
		if (p == 53) {
			end = 0;
			break;
		}
		if (whoturn == 1) {
			whoturn = 2;
		}
		else if (whoturn == 2) {
			whoturn = 1;
		}
	}
	if (trashone < trashtwo) {
		cout << "You win." << endl;
	}
	else if (trashtwo < trashone) {
		cout << "Computer win." << endl;
	}
	else if (trashone == trashtwo) {
		cout << "It's deuce." << endl;
	}
	cout << endl;
}
void card::checkcard(int n) {
	if (n == 7 || n == 20 || n == 33 || n == 46) {
		howcard = 1;//可出牌
	}
	else {
		if (14 <= n && n <= 26) {//紅心heart
			if (14 <= n && n <= 19) {
				if (n == cardtable[3][1]-1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
			else if (21 <= n && n <= 26) {
				if (n == cardtable[1][1]+1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
		}
		else if (27 <= n && n <= 39) {//黑桃spade
			if (27 <= n && n <= 32) {
				if (n == cardtable[3][2]-1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
			else if (34 <= n && n <= 39) {
				if (n == cardtable[1][2]+1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
		}
		else if (1 <= n && n <= 13) {//方塊diamond
			if (1 <= n && n <= 6) {
				if (n == cardtable[3][3]-1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
			else if (8 <= n && n <= 13) {
				if (n == cardtable[1][3]+1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
		}
		else if (40 <= n && n <= 52) {//梅花clubs
			if (40 <= n && n <= 45) {
				if (n == cardtable[3][4]-1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
			else if (47 <= n && n <= 52) {
				if (n == cardtable[1][4]+1) {
					howcard = 1;
				}
				else {
					howcard = 2;//只能蓋牌
				}
			}
		}
	}
}
void card::cardplayed(int n) {
	int num, suit;//num牌數字,suit牌花色代碼
	if (n == 7 || n == 20 || n == 33 || n == 46) {
		if (n == 20) {
			cardtable[2][1] = 20;
		}
		else if (n == 33) {
			cardtable[2][2] = 33;
		}
		else if (n == 7) {
			cardtable[2][3] = 7;
		}
		else if (n == 46) {
			cardtable[2][4] = 46;
		}
	}
	else {
		if (14 <= n && n <= 26) {//紅心heart
			if (14 <= n && n <= 19) {
				if (n < cardtable[3][1]) {
					cardtable[3][1] = n;
				}
			}
			else if (21 <= n && n <= 26) {
				if (n > cardtable[1][1]) {
					cardtable[1][1] = n;
				}
			}
		}
		else if (27 <= n && n <= 39) {//黑桃spade
			if (27 <= n && n <= 32) {
				if (n < cardtable[3][2]) {
					cardtable[3][2] = n;
				}
			}
			else if (34 <= n && n <= 39) {
				if (n > cardtable[1][2]) {
					cardtable[1][2] = n;
				}
			}
		}
		else if (1 <= n && n <= 13) {//方塊diamond
			if (1 <= n && n <= 6) {
				if (n < cardtable[3][3]) {
					cardtable[3][3] = n;
				}
			}
			else if (8 <= n && n <= 13) {
				if (n > cardtable[1][3]) {
					cardtable[1][3] = n;
				}
			}
		}
		else if (40 <= n && n <= 52) {//梅花clubs
			if (40 <= n && n <= 45) {
				if (n < cardtable[3][4]) {
					cardtable[3][4] = n;
				}
			}
			else if (47 <= n && n <= 52) {
				if (n > cardtable[1][4]) {
					cardtable[1][4] = n;
				}
			}
		}
	}
	cout << endl;
	for (int i = 0; i < 15; i++) {
		for (int j = 1; j < 5; j++) {
			suit = cardtable[1][j] / 13 + 1;
			num = cardtable[1][j] % 13;
			if (num == 0) {
				suit--;
				num = 13;
			}
			if (num != 7) {
				if (i == 0) {
					cout << " ";
					setcolor(249);//白底字藍
					cout << "                   ";
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (i == 1) {
					cout << " ";
					setcolor(249);//白底字藍
					if (num == 1) {
						cout << "  A                ";
					}
					else if (2 <= num && num <= 9) {
						cout << "  " << num << "                ";
					}
					else if (num == 10) {
						cout << "  " << num << "               ";
					}
					else if (num == 11) {
						cout << "  J                ";
					}
					else if (num == 12) {
						cout << "  Q                ";
					}
					else if (num == 13) {
						cout << "  K                ";
					}
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (2 <= i && i <= 12) {
					cout << " ";
					typeone(suit);
					if (suit == 1 || suit == 2) {
						setcolor(252);//白底字紅
					}
					else if (suit == 3 || suit == 4 ) {
						setcolor(240);//白底字黑
					}
					cout << " ";
					for (int k = 0; k <= 16; k++) {
						cout << cardpicone[i-2][k];
					}
					cout << " ";
					setcolor(7);//黑底字白
					cout << " " ;
				}
				else if (i == 13) {
					cout << " ";
					setcolor(249);//白底字藍
					if (num == 1) {
						cout << "                A  ";
					}
					else if (2 <= num && num <= 9) {
						cout << "                " << num << "  ";
					}
					else if (num == 10) {
						cout << "               " << num << "  ";
					}
					else if (num == 11) {
						cout << "                J  ";
					}
					else if (num == 12) {
						cout << "                Q  ";
					}
					else if (num == 13) {
						cout << "                K  ";
					}
					setcolor(7);//黑底字白
					cout << " ";
				}
				if (i == 14) {
					cout << " ";
					setcolor(249);//白底字藍
					cout << "                   " ;
					setcolor(7);//黑底字白
					cout << " ";
				}
			}
			if (num == 7) {
				cout << " ";
				cout << "###################";
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 15; i++) {
		for (int j = 1; j < 5; j++) {
			suit = cardtable[2][j] / 13 + 1;
			num = cardtable[2][j] % 13;
			if (num == 0) {
				suit--;
				num = 13;
			}
			if (num == 7) {
				if (i == 0) {
					cout << " ";
					setcolor(249);//白底字藍
					cout << "                   ";
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (i == 1) {
					cout << " ";
					setcolor(249);//白底字藍
					if (num == 1) {
						cout << "  A                ";
					}
					else if (2 <= num && num <= 9) {
						cout << "  " << num << "                ";
					}
					else if (num == 10) {
						cout << "  " << num << "               ";
					}
					else if (num == 11) {
						cout << "  J                ";
					}
					else if (num == 12) {
						cout << "  Q                ";
					}
					else if (num == 13) {
						cout << "  K                ";
					}
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (2 <= i && i <= 12) {
					cout << " ";
					typeone(suit);
					if (suit == 1 || suit == 2) {
						setcolor(252);//白底字紅
					}
					else if (suit == 3 || suit == 4) {
						setcolor(240);//白底字黑
					}
					cout << " ";
					for (int k = 0; k <= 16; k++) {
						cout << cardpicone[i - 2][k];
					}
					cout << " ";
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (i == 13) {
					cout << " ";
					setcolor(249);//白底字藍
					if (num == 1) {
						cout << "                A  ";
					}
					else if (2 <= num && num <= 9) {
						cout << "                " << num << "  ";
					}
					else if (num == 10) {
						cout << "               " << num << "  ";
					}
					else if (num == 11) {
						cout << "                J  ";
					}
					else if (num == 12) {
						cout << "                Q  ";
					}
					else if (num == 13) {
						cout << "                K  ";
					}
					setcolor(7);//黑底字白
					cout << " ";
				}
				if (i == 14) {
					cout << " ";
					setcolor(249);//白底字藍
					cout << "                   ";
					setcolor(7);//黑底字白
					cout << " ";
				}
			}
			if (num != 7) {
				cout << " ";
				cout << "###################";
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 15; i++) {
		for (int j = 1; j < 5; j++) {
			suit = cardtable[3][j] / 13 + 1;
			num = cardtable[3][j] % 13;
			if (num == 0) {
				suit--;
				num = 13;
			}
			if (num != 7) {
				if (i == 0) {
					cout << " ";
					setcolor(249);//白底字藍
					cout << "                   ";
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (i == 1) {
					cout << " ";
					setcolor(249);//白底字藍
					if (num == 1) {
						cout << "  A                ";
					}
					else if (2 <= num && num <= 9) {
						cout << "  " << num << "                ";
					}
					else if (num == 10) {
						cout << "  " << num << "               ";
					}
					else if (num == 11) {
						cout << "  J                ";
					}
					else if (num == 12) {
						cout << "  Q                ";
					}
					else if (num == 13) {
						cout << "  K                ";
					}
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (2 <= i && i <= 12) {
					cout << " ";
					typeone(suit);
					if (suit == 1 || suit == 2) {
						setcolor(252);//白底字紅
					}
					else if (suit == 3 || suit == 4) {
						setcolor(240);//白底字黑
					}
					cout << " ";
					for (int k = 0; k <= 16; k++) {
						cout << cardpicone[i - 2][k];
					}
					cout << " ";
					setcolor(7);//黑底字白
					cout << " ";
				}
				else if (i == 13) {
					cout << " ";
					setcolor(249);//白底字藍
					if (num == 1) {
						cout << "                A  ";
					}
					else if (2 <= num && num <= 9) {
						cout << "                " << num << "  ";
					}
					else if (num == 10) {
						cout << "               " << num << "  ";
					}
					else if (num == 11) {
						cout << "                J  ";
					}
					else if (num == 12) {
						cout << "                Q  ";
					}
					else if (num == 13) {
						cout << "                K  ";
					}
					setcolor(7);//黑底字白
					cout << " ";
				}
				if (i == 14) {
					cout << " ";
					setcolor(249);//白底字藍
					cout << "                   ";
					setcolor(7);//黑底字白
					cout << " ";
				}
			}
			if (num == 7) {
				cout << " ";
				cout << "###################";
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}