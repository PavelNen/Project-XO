

int N = 0; //Количество пустых клеток
unsigned int n;
//#define n 7

int num = 0;
char r = 'n';
bool win = false, lose = false;
char **f;

#include"XOfun.h"
using namespace std;

/*//Устанавливает цвет текста в консоли
void SetColor(int text)
{
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hStdOut, (WORD)text);
}*/

// устанавливает цвет текста и подложки в консоли 
 void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

//Инициализация пустого матрицы поля
 void ini(char **f, int n){
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			f[i][j] = ' ';
		}
	}
}

//Сохранение матрицы в файл
 bool save(char **f, int & x, int & y){
	ofstream fout("Save.XO");
	if (!fout){ return false; }
	else{
		fout << x << ' ' << y << ' ';
		fout << n;
		for (unsigned i = 0; i < n; i++)
		{
			for (unsigned j = 0; j < n; j++)
			{
				if (f[i][j] != '#'){ fout << f[i][j]; }
				else{ fout << ' '; }
			}
		}
		//		fout << endl;

		return true;
	}

}

//Загрузка матрицы из файла
 bool load(int & x, int & y){
	ifstream fin("Save.XO");
	if (!fin || fin.eof()){ return false; }
	else{
		string str;
		fin >> x >> y >> n;
		//	delete[] *f;
		f = new char *[n];
		for (unsigned int i = 0; i < n; i++)
		{
			f[i] = new char[n];
		}
		getline(fin, str);
		unsigned int k = 0;
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
				f[i][j] = str[k++];
				if (f[i][j] == ' '){ N++; }
			}
		}
		//		fin >> x >> y;
		return true;
	}

}

//Рисование текущего поля с ходами игроков
 void graph(char **f, int n, int x, int y, int & xcomp, int & ycomp){
	//Верхняя граница
	cout << "\xDA";	// ?
	for (int j = 0; j < 2 * n - 1; j++)
	{
		if (j % 2 == 0)
		{
			cout << "\xC4";	// ?
		}
		else
		{
			cout << "\xC2";	// ?
		}
	}
	cout << "\xBF" << endl;	// ?

	//Серёдка
	for (int i = 0; i < n - 1; i++)
	{

		cout << "\xB3";	// ?
		for (int j = 0; j < n; j++)
		{
			//	if (i == x & j == y){ system("color 2C"); }
			//	else system("color 0C");
			if ((win || lose) & r == 'h' & i == num){ SetColor(12, 15); }
			else if ((win || lose) & r == 'v' & j == num){ SetColor(12, 15); }
			else if ((win || lose) & r == 'd' & num == 1 & i == j){ SetColor(12, 15); }
			else if ((win || lose) & r == 'd' & num == 2 & i == n - 1 - j){ SetColor(12, 15); }
			if (f[i][j] == '#'){ SetColor(12, 15); }
			if (i == ycomp & j == xcomp){ SetColor(13, 15); }
			cout << f[i][j];	// ?
			SetColor(0, 15);
			cout << "\xB3";
		}
		cout << endl;

		//Между строк
		cout << "\xC3";	// ?
		for (int j = 0; j < n - 1; j++)
		{
			cout << "\xC4" << "\xC5";	// ?
		}
		cout << "\xC4" << "\xB4" << endl;	// ?
	}

	cout << "\xB3";	// ?
	for (int j = 0; j < n; j++)
	{
		if ((win || lose) & r == 'h' & n - 1 == num){ SetColor(12, 15); }
		else if ((win || lose) & r == 'v' & j == num){ SetColor(12, 15); }
		else if ((win || lose) & r == 'd' & num == 1 & n - 1 == j){ SetColor(12, 15); }
		else if ((win || lose) & r == 'd' & num == 2 & 0 == j){ SetColor(12, 15); }
		if (f[n - 1][j] == '#'){ SetColor(12, 15); }
		if (n - 1 == ycomp & j == xcomp){ SetColor(13, 15); }
		cout << f[n - 1][j];	// ?
		SetColor(0, 15);
		cout << "\xB3";
	}
	cout << endl;

	//Нижняя граница
	cout << "\xC0"; // ?
	for (int j = 0; j < 2 * n - 1; j++)
	{
		if (j % 2 == 0)
		{
			cout << "\xC4";	// ?
		}
		else
		{
			cout << "\xC1";	// ?
		}
	}
	cout << "\xD9" << endl;	// ?
}

//Движение курсора
 void cursor(char **f, int n, int & x, int & y, int cmd){
	int i, j;
	//f[y][x] = ' ';
	if (N > 0){
		switch (cmd)
		{
		case 1:
			//UP
		{
			/*for (j = y; f[x][j] != ' ' || j>-1 || j!=y; j--)
			{
			if (j == 0) { j = n - 1; }
			}
			y = j;*/

			j = y;
			do {
				/*if (i < n - 1 & j < n - 1) { i++; j++; }
				else if (i == n - 1 & j < n - 1) { i = 0; j++; }
				else if (i < n - 1 & j == n - 1){ i++; j = 0; }
				else if (i == n - 1 & j == n - 1) { i = 0; j = 0; }*/

				if (j > 0){ j--; }
				else{ j = n - 1; }

			} while (f[j][x] != ' ');

			y = j;
		} break;

		case 2:
			//DOWN
		{
			j = y;
			do {
				if (j < n - 1){ j++; }
				else{ j = 0; }

			} while (f[j][x] != ' ');

			y = j;
		} break;

		case 3:
			//LEFT
		{
			i = y; j = x;
			do {
				if (j > 0) { j--; }
				else if ((j == 0) & (i > 0)) { j = n - 1; i--; }
				else if ((j == 0) & (i == 0)) { j = n - 1; i = n - 1; }

				//	if (i > 0){ i--; }
				//	else{ i = n-1; }
				//	if (j > 0){ j--; }
				//	else{ j = n-1; }

			} while (f[i][j] != ' ');

			x = j; y = i;
		} break;

		case 4:
			//RIGHT
		{
			i = y; j = x;
			do {
				//if (i < n - 1){ i++; }	else{ i = 0; }
				//if (j < n - 1){ j++; }	else{ j = 0; }
				if (j < n - 1) { j++; }
				else if (j == n - 1 & i < n - 1) { j = 0; i++; }
				else if (i == n - 1 & j == n - 1) { i = 0; j = 0; }



			} while (f[i][j] != ' ');

			x = j; y = i;
		} break;
		default:
			break;
		}
		f[y][x] = '#';
	}
}

//Проверка на победителя
 bool winfind(char **f, int n, int x, int y, char c){
	bool w = false, wt;

	//Горизонталь
	wt = true;
	for (int i = 0; i < n; i++)
	{
		if (f[y][i] != c)
		{
			wt = false;
		}
	}
	w += wt;
	if (wt){ num = y; r = 'h'; }
	//Вертикаль
	wt = true;
	for (int i = 0; i < n; i++)
	{
		if (f[i][x] != c)
		{
			wt = false;
		}
	}
	w += wt;
	if (wt){ num = x; r = 'v'; }
	//Диагональ \
		
	if (x == y){
		wt = true;
		for (int i = 0; i < n; i++)
		{
			if (f[i][i] != c)
			{
				wt = false;
			}
		}
		w += wt;
		if (wt){ num = 1; r = 'd'; }
	}
	//Диагональ /
	if (x == n - y - 1){
		wt = true;
		for (int i = 0; i < n; i++)
		{
			if (f[n - 1 - i][i] != c)
			{
				wt = false;
			}
		}
		w += wt;
		if (wt){ num = 2; r = 'd'; }
	}
	return w;
}

//Ход компьютера
void comp(char **f, int n, int & xcomp, int & ycomp, int & x, int & y){
	set<int> withX, withO;
	int *m = new int[n]; //Кол-во элементов в каждом ряду
	int i, j, k;
	int kymin = n, kxmin = n, k1min = n, k2min = 0;
	int kyminX = n, kxminX = n, k1minX = n, k2minX = 0;
	bool ok = true;
	set <int> vert, hor, kmin, vertX, horX, kminX;

	kmin.insert(n);
	kminX.insert(n);

	//Анализ ситуации с ноликами
	k = 0;
	f[y][x] = ' ';
	//Horisontal
	for (i = 0; i < n; i++)
	{
		k = 0;
		ok = true;
		for (j = 0; j < n; j++)
		{
			if (f[i][j] == ' '){ k++; }
			if (f[i][j] == 'X'){ ok = false; withX.insert(i); }
		}
		if (ok){ m[i] = k; }
		else { m[i] = -1; }
		if (k <= kymin & ok){ kymin = k; kmin.insert(kymin); }
	}

	for (i = 0; i < n; i++)
	{
		if (withX.find(i) == withX.end()){
			if (m[i] == kymin){ hor.insert(i); }
		}
	}

	withX.clear();

	//Verticals
	for (j = 0; j < n; j++)
	{
		k = 0;
		ok = true;
		for (i = 0; i < n; i++)
		{
			if (f[i][j] == ' '){ k++; }
			if (f[i][j] == 'X'){ ok = false; withX.insert(j); }
		}
		if (ok){ m[j] = k; }
		else { m[j] = -1; }
		if (k <= kxmin & ok){ kxmin = k; kmin.insert(kxmin); }
	}

	for (j = 0; j < n; j++)
	{
		if (withX.find(j) == withX.end()){
			if (m[j] == kxmin){ vert.insert(j); }
		}
	}

	withX.clear();

	//Diagonals

	// \ d
	k = 0;
	ok = true;
	for (i = 0; i < n; i++)
	{
		if (f[i][i] == ' '){ k++; }
		if (f[i][i] == 'X'){ ok = false; }
	}
	if (ok){ k1min = k; kmin.insert(k1min); }
	else{ k1min = -1; }

	// / d
	k = 0;
	ok = true;
	for (i = 0; i < n; i++)
	{
		if (f[i][n - 1 - i] == ' '){ k++; }
		if (f[i][n - 1 - i] == 'X'){ ok = false; }
	}
	if (ok){ k2min = k; kmin.insert(k2min); }
	else{ k2min = -1; }


	withX.clear();

	//Анализ ситуации с крестиками
	k = 0;
	f[y][x] = ' ';
	//Horisontal
	for (i = 0; i < n; i++)
	{
		k = 0;
		ok = true;
		for (j = 0; j < n; j++)
		{
			if (f[i][j] == ' '){ k++; }
			if (f[i][j] == 'O'){ ok = false; withO.insert(i); }
		}
		if (ok){ m[i] = k; }
		else { m[i] = -1; }
		if (k <= kyminX & ok){ kyminX = k; kminX.insert(kyminX); }
	}

	for (i = 0; i < n; i++)
	{
		if (withO.find(i) == withO.end()){
			if (m[i] == kyminX){ horX.insert(i); }
		}
	}

	withO.clear();

	//Verticals
	for (j = 0; j < n; j++)
	{
		k = 0;
		ok = true;
		for (i = 0; i < n; i++)
		{
			if (f[i][j] == ' '){ k++; }
			if (f[i][j] == 'O'){ ok = false; withO.insert(j); }
		}
		if (ok){ m[j] = k; }
		else { m[j] = -1; }
		if (k <= kxminX & ok){ kxminX = k; kminX.insert(kxminX); }
	}

	for (j = 0; j < n; j++)
	{
		if (withO.find(j) == withO.end()){
			if (m[j] == kxminX){ vertX.insert(j); }
		}
	}

	withO.clear();

	//Diagonals

	// \ d
	k = 0;
	ok = true;
	for (i = 0; i < n; i++)
	{
		if (f[i][i] == ' '){ k++; }
		if (f[i][i] == 'X'){ ok = false; }
	}
	if (ok){ k1minX = k; kminX.insert(k1minX); }
	else{ k1minX = -1; }

	// / d
	k = 0;
	ok = true;
	for (i = 0; i < n; i++)
	{
		if (f[i][n - 1 - i] == ' '){ k++; }
		if (f[i][n - 1 - i] == 'X'){ ok = false; }
	}
	if (ok){ k2minX = k; kminX.insert(k2minX); }
	else{ k2minX = -1; }


	withO.clear();


	//Сам ход
	if (!kmin.empty()){
	if (*min_element(kmin.begin(), kmin.end()) <= *min_element(kminX.begin(), kminX.end())){
			if (*min_element(kmin.begin(), kmin.end()) == kymin) {
				do {
					i = rand() % n;
					j = rand() % n;


				} while (!(f[i][j] == ' ' & hor.find(i) != hor.end()));

				f[i][j] = 'O';
			}
			else if (*min_element(kmin.begin(), kmin.end()) == kxmin) {
				do {
					i = rand() % n;
					j = rand() % n;


				} while (!(f[i][j] == ' ' & vert.find(j) != vert.end()));

				f[i][j] = 'O';
			}
			else if (*min_element(kmin.begin(), kmin.end()) == k1min) {
				do {
					i = rand() % n;
					j = rand() % n;


				} while (!(f[i][j] == ' ' & i == j));

				f[i][j] = 'O';
			}
			else if (*min_element(kmin.begin(), kmin.end()) == kymin) {
				do {
					i = rand() % n;
					j = rand() % n;


				} while (!(f[i][j] == ' ' & i == j));

				f[i][j] = 'O';
			}

			xcomp = j;
			ycomp = i;

			if (f[y][x] == 'O'){ cursor(f, n, x, y, 4); }
			if (N > 0){ f[y][x] = '#'; }
			N--;
		}
	else{
		if (*min_element(kminX.begin(), kminX.end()) == kyminX) {
			do {
				i = rand() % n;
				j = rand() % n;


			} while (!(f[i][j] == ' ' & horX.find(i) != horX.end()));

			f[i][j] = 'O';
		}
		else if (*min_element(kminX.begin(), kminX.end()) == kxminX) {
			do {
				i = rand() % n;
				j = rand() % n;


			} while (!(f[i][j] == ' ' & vertX.find(j) != vertX.end()));

			f[i][j] = 'O';
		}
		else if (*min_element(kminX.begin(), kminX.end()) == k1minX) {
			do {
				i = rand() % n;
				j = rand() % n;


			} while (!(f[i][j] == ' ' & i == j));

			f[i][j] = 'O';
		}
		else if (*min_element(kminX.begin(), kminX.end()) == kyminX) {
			do {
				i = rand() % n;
				j = rand() % n;


			} while (!(f[i][j] == ' ' & i == j));

			f[i][j] = 'O';
		}

		xcomp = j;
		ycomp = i;

		N--;
		if (f[y][x] == 'O'){ cursor(f, n, x, y, 4); }
		if (N > 0){ f[y][x] = '#'; }
		
	}
	}
		else { N = 0; }
	

}