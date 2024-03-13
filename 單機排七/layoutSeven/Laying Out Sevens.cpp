#include <iostream>
#include <string>
#include "card.h"
using namespace std;

int main() {
	int i;
	i = 1;
	card card1;
	card1.cardinorder();
	while (i = 1) {
		int mode, dif;
		cout<<"Enter the number of what you want to do : " << endl << "(1:Start the game. 0 : End this program.)"<< endl;
		cin >> mode;
		cout << "Choose the difficulty.(1:Easy  2:???)" << endl;
		cin >> dif;
		if (1 > dif || dif > 2) {
			cout << "Wrong enter." << endl << endl;
			continue;
		}
		if (0 > mode || mode > 1) {
			cout << "Wrong enter." << endl << endl;
			continue;
		}
		if (mode == 0) {
			i = 0;
			break;
		}
		else if (mode == 1) {
			card1.randomcard(52);
			cout << endl << "Game rule : " << endl;
			cout << "1.玩家擁有spade7者必須先出，擁有（其餘heart7、diamond7、club7）者必須接續出牌，如手中沒有任何一張7可以直接開始接7，遊戲過程中玩家須維持輪流出牌。" << endl;
			cout << "2.出牌方式必須接續同花色且依照數字順序（往上由7至K，往下由6至A）。" << endl;
			cout << "3.當有人沒辦法出牌時，該玩家需要覆蓋一張牌。" << endl;
			cout << "4.當其中一個花色順利從A接到K該花色就結束接牌。(注意同一排必須同花色否則不算)" << endl;
			cout << "5.最後以覆蓋的牌總點數多寡來決定勝負，點數最少者獲勝。(A為一點，2為兩點，以此類推K為13點)" << endl<<endl;
			cout << "Game start." << endl<<endl;
			cout << "The cards you have is ";
			card1.getplayerscard();
			cout << endl;
			card1.seven(dif);
		}
	}
}
