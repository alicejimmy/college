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
			cout << "1.���a�֦�spade7�̥������X�A�֦��]��lheart7�Bdiamond7�Bclub7�^�̥�������X�P�A�p�⤤�S������@�i7�i�H�����}�l��7�A�C���L�{�����a���������y�X�P�C" << endl;
			cout << "2.�X�P�覡��������P���B�̷ӼƦr���ǡ]���W��7��K�A���U��6��A�^�C" << endl;
			cout << "3.���H�S��k�X�P�ɡA�Ӫ��a�ݭn�л\�@�i�P�C" << endl;
			cout << "4.��䤤�@�Ӫ�ⶶ�Q�qA����K�Ӫ��N�������P�C(�`�N�P�@�ƥ����P���_�h����)" << endl;
			cout << "5.�̫�H�л\���P�`�I�Ʀh��ӨM�w�ӭt�A�I�Ƴ̤֪���ӡC(A���@�I�A2�����I�A�H������K��13�I)" << endl<<endl;
			cout << "Game start." << endl<<endl;
			cout << "The cards you have is ";
			card1.getplayerscard();
			cout << endl;
			card1.seven(dif);
		}
	}
}
