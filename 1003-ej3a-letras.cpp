#include "upc.h"

#define TOP 2
#define RIGHT 89
#define BOTTOM 22
#define LEFT 10

#define DROPCHANCE 10
#define MAXDROPS 201
#define DELAY 50

using namespace std;

bool dropFalls() {
	return randint(0, 100) < DROPCHANCE;
}

int main() {
	srand(time(nullptr));
	int* x = new int[MAXDROPS];
	int* y = new int[MAXDROPS];
	int* color = new int[MAXDROPS];
	char* ch = new char[MAXDROPS];
	int numdrops = 0;
	int fallspeed = 1;

	for (;;) {
		for (int i = LEFT; i <= RIGHT; ++i) {
			if (dropFalls() && numdrops < MAXDROPS) {
				x[numdrops] = i;
				y[numdrops] = TOP;
				color[numdrops] = randint(0, 16);
				ch[numdrops] = randint('A', 'Z' + 1);
				++numdrops;
			}
		}
		clear();
		for (int i = 0; i < numdrops; ++i) {
			if (y[i] < BOTTOM) {
				gotoxy(x[i], y[i]);
				foreground(color[i]);
				cout << ch[i];
				y[i] += fallspeed;
			} else {
				--numdrops;
				x[i] = x[numdrops];
				y[i] = y[numdrops];
				color[i] = color[numdrops];
				ch[i] = ch[numdrops];
			}
		}
		gotoxy(0, 0);
		sleep4(DELAY);
	}
	clearColor();

	delete[] x;
	delete[] y;
	delete[] color;
	delete[] ch;

	return 0;
}