#include "upc.h"

#define TOP 2
#define RIGHT 89
#define BOTTOM 22
#define LEFT 10

#define DROPCHANCE 10
#define MAXDROPS 201

using namespace std;

bool dropFalls() {
	return randint(0, 100) < DROPCHANCE;
}

/* agrega un elemento al final de un arreglo si hay espacio */
bool push_back(int* a, int& n, int elem, int MAX = MAXDROPS) {
	if (n < MAX) {
		a[n++] = elem;
		return true;
	} else {
		return false;
	}
}

/* agrega un elemento al final de un arreglo si hay espacio */
bool push_back(char* a, int& n, char elem, int MAX = MAXDROPS) {
	if (n < MAX) {
		a[n++] = elem;
		return true;
	} else {
		return false;
	}
}

/* eliminar elemento de un arreglo si no interesa el orden */
bool remove(int* a, int& n, int i) {
	if (n > 0) {
		--n;
		a[i] = a[n];
		return true;
	} else {
		return false;
	}
}
bool remove(char* a, int& n, int i) {
	if (n > 0) {
		--n;
		a[i] = a[n];
		return true;
	} else {
		return false;
	}
}

int main() {
	srand(time(nullptr));

	int* x = new int[MAXDROPS];
	int nx = 0;

	int* y = new int[MAXDROPS];
	int ny = 0;

	int* chcolor = new int[MAXDROPS];
	int nchcolor = 0;

	char* ch = new char[MAXDROPS];
	int nch = 0;

	int mx = (RIGHT + LEFT) / 2;
	int my = BOTTOM - 2;

	int fallspeed = 1;
	int delay = 250;
	bool leave = false;

	while (!leave) {
		for (int i = LEFT; i <= RIGHT; ++i) {
			if (dropFalls() && nx < MAXDROPS) {
				push_back(x, nx, i);
				push_back(y, ny, TOP);
				push_back(chcolor, nchcolor, randint(0, 16));
				push_back(ch, nch, randint('A', 'Z' + 1));
			}
		}
		clear();
		clearColor();
		for (int i = 0; i < nx; ++i) {
			if (y[i] < BOTTOM) {
				gotoxy(x[i], y[i]);
				color(chcolor[i]);
				cout << ch[i];
				y[i] += fallspeed;
				if (mx == x[i] && my == y[i]) {
					clear();
					gotoxy(0, 0);
					color(BRIGHT_RED);
					cout << "GAME OVER!";
					leave = true;
					break;
				}
			} else {
				remove(x, nx, i);
				remove(y, ny, i);
				remove(chcolor, nchcolor, i);
				remove(ch, nch, i);
			}
		}
		if (leave) break;
		gotoxy(mx, my);
		color(DARK_YELLOW, BRIGHT_YELLOW);
		cout << (char)2;
		clearColor();
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 'x': leave = true; break;
			case 'a': --mx; break;
			case 'd': ++mx; break;
			}
		}

		gotoxy(0, 0);
		sleep4(delay);
	}
	clearColor();

	delete[] x;
	delete[] y;
	delete[] chcolor;
	delete[] ch;

	return 0;
}