//#pragma comment (lib, "kernel32.lib")

#pragma once



#include"XOfun.h"
//#include"XOfun.cpp"


using namespace std;




//typedef BOOL(WINAPI * LPSetConsoleFont)(HANDLE, DWORD);

int main(){
//	LPSetConsoleFont SetConsoleFont = reinterpret_cast<LPSetConsoleFont>(GetProcAddress(GetModuleHandle("kernel32.dll"), "SetConsoleFont"));
//	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 6);

//	SetConsoleCP(1251);  SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Russian");

tut:

	//Start screen
	system("mode con cols=70 lines=40");

	system("color F0");
	SetColor(12, 15);
	cout << "		GAME - XO" << endl << endl;
	SetColor(0, 15);
	cout << "	Press" << endl;
	cout << " n to play new game or" << endl;
	cout << " l to play load last game" << endl;

	char ch;
	


/*	char **f = new char *[2];
	for (int i = 0; i < 2; i++)
	{
		f[i] = new char[2];
	}
*/

	int x, y;
	while (true){
		while (ch = getch()){
			switch (ch)
			{
			case 'n': goto newgame;
			case 'l': if (load(x, y)){ goto start; } break;
			default:
				break;
			}
		}
	}

newgame:
	system("cls");
	system("color F0");
	SetColor(12, 15);
	cout << "	Привеет!" << endl << endl;
	SetColor(0, 15);
	cout << " Keyboard control:" << endl;
	cout << " ARROWS - move cursor" << endl;
	cout << " SPACE - set X" << endl;
	cout << " r - repeat game after it's end" << endl;
	cout << " q - exit with save" << endl << endl;
	cout << "	Enter size of game field and press ENTER to start XO:	";

	cin >> n;
	cout << endl;
	if (n < 3){ goto tut; }
//	while (ch = getch() != ' '){}
	
	x = n / 2; y = n / 2;
	int xcomp, ycomp; //Координаты компа

//	delete[] *f;
	f = new char *[n];
	for (int i = 0; i < n; i++)
	{
		f[i] = new char[n];
	}

repeat:
	ini(f);
	N = n*n;

start:
	win = false; lose = false;
	system("cls");

	srand(time(NULL));

	//Возможность первого хода для компа
	xcomp = rand() % n;
	ycomp = rand() % n;
	if (1 == rand() % 3){
		f[ycomp][xcomp] = 'O';
		N--;
	} 

	if (f[y][x] == 'O'){ x++; }

	f[y][x] = '#';

	//Игра началась
	
	graph(f, x, y, xcomp, ycomp);
	cout << "Free boxes: " << N;
	while (true){
		while (ch = getch()){
			switch (ch)
			{
				/*
			case '7': f[0][0] = 'X'; break;
			case '8': f[0][1] = 'X'; break;
			case '9': f[0][2] = 'X'; break;
			case '4': f[1][0] = 'X'; break;
			case '5': f[1][1] = 'X'; break;
			case '6': f[1][2] = 'X'; break;
			case '1': f[2][0] = 'X'; break;
			case '2': f[2][1] = 'X'; break;
			case '3': f[2][2] = 'X'; break;*/

			case 72: f[y][x] = ' '; cursor(f, x, y, 1); break;	//move UP
			case 80: f[y][x] = ' '; cursor(f, x, y, 2); break;	//move DOWN
			case 75: f[y][x] = ' '; cursor(f, x, y, 3); break;	//move LEFT
			case 77: f[y][x] = ' '; cursor(f, x, y, 4); break;	//move RIGHT
			case ' ':  
				system("cls");
				//Мой ход
				f[y][x] = 'X'; N--;
				win=winfind(f, x, y, 'X');
				if (win){ graph(f, x, y, xcomp, ycomp); cout << "You WIN!!!"; goto end; }
				cursor(f, x, y, 4);
				//Его ход
				comp(f, xcomp, ycomp, x, y);
				if (N > 0){

					lose = winfind(f, xcomp, ycomp, 'O');
					if (lose){ graph(f, x, y, xcomp, ycomp); cout << "Sorry..."; goto end; }
					if (x == xcomp & y == ycomp){ cursor(f, x, y, 4); }
				}
			//	xcomp = rand() % n;
			//	ycomp = rand() % n;
				break;
			case 'q': if (!win & !lose){ save(f, x, y); }  exit(0);
			}
			system("cls");
			graph(f, x, y, xcomp, ycomp);
			if (!win & !lose & N == 0){ cout << "Draw!"; goto end; }
			cout << "Free boxes: " << N;
		}
		
	}

end:

	cout << endl << "Press r to repeat, n to new game or q to quit..." << endl;
	while (true){
		while (ch = getch()){
			switch (ch)
			{
			case 'r': goto repeat;
			case 'n': goto newgame;
			case 'q': exit(0);
			}
		}
	}
	
}