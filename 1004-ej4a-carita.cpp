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

int main() {
	srand(time(nullptr));
	int* x = new int[MAXDROPS];
	int* y = new int[MAXDROPS];
	int* chcolor = new int[MAXDROPS];
	char* ch = new char[MAXDROPS];

	int mx = (RIGHT + LEFT) / 2;
	int my = BOTTOM - 2;

	int numdrops = 0;
	int fallspeed = 1;
	int delay = 250;
	bool leave = false;

	while (!leave) {
		for (int i = LEFT; i <= RIGHT; ++i) {
			if (dropFalls() && numdrops < MAXDROPS) {
				x[numdrops] = i;
				y[numdrops] = TOP;
				chcolor[numdrops] = randint(0, 16);
				ch[numdrops] = randint('A', 'Z' + 1);
				++numdrops;
			}
		}
		clear();
		clearColor();
		for (int i = 0; i < numdrops; ++i) {
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
				--numdrops;
				x[i] = x[numdrops];
				y[i] = y[numdrops];
				chcolor[i] = chcolor[numdrops];
				ch[i] = ch[numdrops];
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