#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <stdlib.h>
using namespace std;

class box {
public:
	void getmap(vector<string> map);
	void game(vector<string> map);
	void findABE();
	void printmap();
	void walk(char);
	void undo(char);
	void gotoxy(int, int);

private:
	int Ax, Ay;
	vector<string> Map;
	vector<char> move;
	vector<vector<int> > End;
};

int main() {
	box box1;
	int s = 1;
	char k[1000];//k �s���
	string f;//f �ɮצW��
	vector<string> map;
	fstream file;
	while (s == 1) {
		map.clear();
		f="";
		box1.gotoxy(0, 0);
		cout << "��J�n�}�Ҫ��ɮצW�� : (��JE�������{��)"<<endl;
		cout << "                                                                                               ";
		box1.gotoxy(0, 1);
		cin >> f;
		if (f == "E") {
			system("CLS");
			cout<<"�����{��";
			s = 0;
			break;
		}
		system("CLS");
		file.open(f.c_str(), ios::in);
		if (!file) {
			box1.gotoxy(0, 2);
			cout << "�ɮ׵L�k�}��!" << endl;
		}
		else {
			box1.gotoxy(0, 2);
			cout << "���\\�}��" << f << endl;
			do {
				file.getline(k, sizeof(k));
				map.push_back(k);
			} while (!file.eof());
			box1.getmap(map);
			box1.game(map);

			file.close();
		}
		
	}
	
}

void box::getmap(vector<string> map) {
	Map.clear();
	Map = map;
}
void box::game(vector<string> map) {
	int f = 1, t = 0;//f 0�C������ 1�٨S���� ,t 0�a�ϨS��E 1�a�Ϧ�E
	char m;//m ���ʤ�V
	move.clear();
	printmap();
	gotoxy(0, 5 + Map.size());
	cout << "�C���W�h : " << endl;
	cout << "/(�N�����) *(�N��D��) A(�N��H���ΥX�o�I) B(�N��c�l) E(�N����I)" << endl << endl;
	cout << "���a�H�u���v���覡���ʽc�l�C�i�H�b�S����ê���]�p���������ê���^�����p�U�A�V���B�k�B�W�B�U���a�貾�ʡA" << endl;
	cout << "�����i����C�N�c�l���ʨ���w�I�A�Y�i�L���C" << endl << endl;
	cout << "�����a���ʽc�l�A������n�`�N�G" << endl;
	cout << "�c�l�u��H�u�Q���v���覡���ʡA����H�u�Q�ԡv���覡�Q���ʡC���p�G���a���������A����������ⰼ�S����ê" << endl;
	cout << "���A�h���a�i�H�³o��Ӥ��P����V�����c�l�C" << endl;
	cout << endl;
	while (f == 1) {
		findABE();
		gotoxy(0, 15+ Map.size());
		cout << "��Jw(�W)s(�U)a(��)d(�k)����A���� : (��JE���������d;��JR���m�����d;��JQ�^��W�@�B)";
		gotoxy(0, 16 + Map.size());
		cout << "                                                                  ";
		gotoxy(0, 16 + Map.size());
		cin >> m;
		if (m == 'w') {
			move.push_back('s');
		}
		else if (m == 's') {
			move.push_back('w');
		}
		else if (m == 'a') {
			move.push_back('d');
		}
		else if (m == 'd') {
			move.push_back('a');
		}
		gotoxy(0, 17 + Map.size());
		cout << "                                                                  ";
		if (m == 'E') {
			f = 0;
			gotoxy(0, 17 + Map.size());
			cout << "�����d�w����";
			break;
		}
		if (m == 'R') {
			move.clear();
			getmap(map);
			printmap();
			continue;
		}
		if (m == 'Q') {
			if (move.size()==0) {
				gotoxy(0, 17 + Map.size());
				cout << "�w�g�S���W�@�B�F" << endl;
			}
			else {
				undo(move[move.size() - 1]);
			}
			printmap();
			continue;
		}
		if (m != 'w' && m != 's' && m != 'a' && m != 'd') {
			gotoxy(0, 17 + Map.size());
			cout << "��J���~" << endl;
			continue;
		}
		else {
			gotoxy(0, 16 + Map.size());
			cout << "                                                                  ";
			walk(m);
			for (int i = 0; i < End.size(); i++) {
				if (Map[End[i][0]][End[i][1]] != 'B'&&Map[End[i][0]][End[i][1]] != 'A') {
					Map[End[i][0]][End[i][1]] = 'E';
				}
			}
		}
		printmap();
		t = 0;
		for (int i = 0; i < End.size(); i++) {
			if (Map[End[i][0]][End[i][1]] == 'B') {
				t = 0;
			}
			else {
				t = 1;
				break;
			}
		}
		if (t == 0) {
			gotoxy(0, 17 + Map.size());
			cout << "�AĹ�F" << endl << endl;
			f = 0;
		}
	}

}

void box::findABE() {
	for (int i = 0; i < Map.size(); i++) {
		for (int j = 0; j < Map[i].size(); j++) {
			if (Map[i][j] == 'A') {
				Ax = j;
				Ay = i;
			}
			else if (Map[i][j] == 'E') {
				vector<int> end;
				end.push_back(i);
				end.push_back(j);
				End.push_back(end);
			}
		}
	}
}

void box::printmap() {
	cout << endl;
	gotoxy(0, 4);
	for (int i = 0; i < Map.size(); i++) {
		for (int j = 0; j < Map[i].size(); j++) {
			cout << Map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void box::walk(char m) {
	int Bx, By;
	if (m == 'w') {
		if (Map[Ay-1][Ax]=='*'||Map[Ay - 1][Ax] == 'E') {
			Map[Ay - 1][Ax] = 'A';
			Map[Ay][Ax] = '*';
			Ax = Ax;
			Ay = Ay - 1;
			
		}
		else if (Map[Ay - 1][Ax] == 'B') {
			Bx = Ax;
			By = Ay - 1;
			if (Map[By - 1][Bx] == '*'|| Map[By - 1][Bx] == 'E') {
				Map[Ay - 1][Ax] = 'A';
				Map[Ay][Ax] = '*';
				Map[By - 1][Bx] = 'B';
				Ax = Ax;
				Ay = Ay - 1;
				Bx = Bx;
				By = By - 1;
				move.pop_back();
				move.push_back('S');
			}
			else {
				move.pop_back();
				gotoxy(0, 17 + Map.size());
				cout << "�e�観��ê��" << endl;
			}
		}
		else {
			move.pop_back();
			gotoxy(0, 17 + Map.size());
			cout << "�e�観��ê��" << endl;
		}
	}
	else if (m == 's') {
		if (Map[Ay + 1][Ax] == '*'|| Map[Ay + 1][Ax] == 'E') {
			Map[Ay + 1][Ax] = 'A';
			Map[Ay][Ax] = '*';
			Ax = Ax;
			Ay = Ay + 1;
			
		}
		else if (Map[Ay + 1][Ax] == 'B') {
			Bx = Ax;
			By = Ay + 1;
			if (Map[By + 1][Bx] == '*' || Map[By + 1][Bx] == 'E') {
				Map[Ay + 1][Ax] = 'A';
				Map[Ay][Ax] = '*';
				Map[By + 1][Bx] = 'B';
				Ax = Ax;
				Ay = Ay + 1;
				Bx = Bx;
				By = By + 1;
				move.pop_back();
				move.push_back('W');
			}
			else {
				move.pop_back();
				gotoxy(0, 17 + Map.size());
				cout << "�e�観��ê��" << endl;
			}
		}
		else {
			move.pop_back();
			gotoxy(0, 17 + Map.size());
			cout << "�e�観��ê��" << endl;
		}
	}
	else if (m == 'a') {
		if (Map[Ay][Ax-1] == '*'|| Map[Ay][Ax - 1] == 'E') {
			Map[Ay][Ax - 1] = 'A';
			Map[Ay][Ax] = '*';
			Ax = Ax - 1;
			Ay = Ay;
			
		}
		else if (Map[Ay][Ax-1] == 'B') {
			Bx = Ax-1;
			By = Ay;
			if (Map[By][Bx-1] == '*' || Map[By][Bx-1] == 'E') {
				Map[Ay][Ax - 1] = 'A';
				Map[Ay][Ax] = '*';
				Map[By][Bx-1] = 'B';
				Ax = Ax - 1;
				Ay = Ay;
				Bx = Bx-1;
				By = By;
				move.pop_back();
				move.push_back('D');
			}
			else {
				move.pop_back();
				gotoxy(0, 17 + Map.size());
				cout << "�e�観��ê��" << endl;
			}
		}
		else {
			move.pop_back();
			gotoxy(0, 17 + Map.size());
			cout << "�e�観��ê��" << endl;
		}
	}
	else if (m == 'd') {
		if (Map[Ay][Ax+1] == '*'|| Map[Ay][Ax + 1] == 'E') {
			Map[Ay][Ax + 1] = 'A';
			Map[Ay][Ax] = '*';
			Ax = Ax+1;
			Ay = Ay;
			
		}
		else if (Map[Ay][Ax + 1] == 'B') {
			Bx = Ax+1;
			By = Ay;
			if (Map[By][Bx + 1] == '*' || Map[By][Bx + 1] == 'E') {
				Map[Ay][Ax + 1] = 'A';
				Map[Ay][Ax] = '*';
				Map[By][Bx + 1] = 'B';
				Ax = Ax + 1;
				Ay = Ay;
				Bx = Bx + 1;
				By = By;
				move.pop_back();
				move.push_back('A');
			}
			else {
				move.pop_back();
				gotoxy(0, 17 + Map.size());
				cout << "�e�観��ê��" << endl;
			}
		}
		else {
			move.pop_back();
			gotoxy(0, 17 + Map.size());
			cout << "�e�観��ê��" << endl;
		}
	}
}

void box::undo(char m) {
	if (m == 'w') {
		Map[Ay - 1][Ax] = 'A';
		Map[Ay][Ax] = '*';
		Ax = Ax;
		Ay = Ay - 1;
		move.pop_back();
	}
	else if (m == 's') {
		Map[Ay + 1][Ax] = 'A';
		Map[Ay][Ax] = '*';
		Ax = Ax;
		Ay = Ay + 1;
		move.pop_back();
	}
	else if (m == 'a') {
		Map[Ay][Ax - 1] = 'A';
		Map[Ay][Ax] = '*';
		Ax = Ax - 1;
		Ay = Ay;
		move.pop_back();
	}
	else if (m == 'd') {
		Map[Ay][Ax + 1] = 'A';
		Map[Ay][Ax] = '*';
		Ax = Ax + 1;
		Ay = Ay;
		move.pop_back();
	}
	else if (m == 'W') {
		Map[Ay - 1][Ax] = 'A';
		Map[Ay][Ax] = 'B';
		Map[Ay+1][Ax] = '*';
		Ax = Ax;
		Ay = Ay - 1;
		move.pop_back();
	}
	else if (m == 'S') {
		Map[Ay + 1][Ax] = 'A';
		Map[Ay][Ax] = 'B';
		Map[Ay-1][Ax] = '*';
		Ax = Ax;
		Ay = Ay + 1;
		move.pop_back();
	}
	else if (m == 'A') {
		Map[Ay][Ax - 1] = 'A';
		Map[Ay][Ax] = 'B';
		Map[Ay][Ax+1] = '*';
		Ax = Ax - 1;
		Ay = Ay;
		move.pop_back();
	}
	else if (m == 'D') {
		Map[Ay][Ax + 1] = 'A';
		Map[Ay][Ax] = 'B';
		Map[Ay][Ax-1] = '*';
		Ax = Ax + 1;
		Ay = Ay;
		move.pop_back();
	}

}

void box::gotoxy(int xpos, int ypos) {
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
