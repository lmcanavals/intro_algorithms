#include "upc.h"

#define TOP 2
#define RIGHT 89
#define BOTTOM 22
#define LEFT 10

#define DROPCHANCE 10
#define MAXDROPS 201

using namespace std;

struct Droplet {
	int x;
	int y;
	int color;
	char ch;
};

bool dropFalls() {
	return randint(0, 100) < DROPCHANCE;
}

/* agrega un elemento al final de un arreglo si hay espacio */
bool push_back(Droplet* a, int& n, Droplet elem, int MAX = MAXDROPS) {
	if (n < MAX) {
		a[n++] = elem;
		return true;
	} else {
		return false;
	}
}

/* eliminar elemento de un arreglo si no interesa el orden */
bool remove(Droplet* a, int& n, int i) {
	if (n > 0) {
		--n;
		a[i] = a[n];
		return true;
	} else {
		return false;
	}
}

void newDrops(Droplet* drops, int& ndrops) {
	for (int i = LEFT; i <= RIGHT; ++i) {
		if (dropFalls() && ndrops < MAXDROPS) {
			push_back(drops,
				ndrops,
				{ i, TOP, randint(0, 16), (char)randint('A', 'Z' + 1) });
		}
	}
}

void drawStuff(Droplet* drops, int& ndrops,
			   int mx, int my,
			   bool leave, int& fallspeed) {
	clear();
	for (int i = 0; i < ndrops; ++i) {
		if (drops[i].y < BOTTOM) {
			gotoxy(drops[i].x, drops[i].y);
			color(drops[i].color);
			cout << drops[i].ch;
			drops[i].y += fallspeed;
			if (mx == drops[i].x && my == drops[i].y) {
				clear();
				gotoxy(0, 0);
				color(BRIGHT_RED);
				cout << "GAME OVER!";
				leave = true;
				break;
			}
		} else {
			remove(drops, ndrops, i);
		}
	}
}

void drawMainCharacter(int mx, int my) {
	gotoxy(mx, my);
	color(DARK_YELLOW, BRIGHT_YELLOW);
	cout << (char)2;
	clearColor();
}

void handleInput(int& mx, int& my, bool& leave) {
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case 'x': leave = true; break;
		case 'a': --mx; break;
		case 'd': ++mx; break;
		}
	}
}

int main() {
	srand(time(nullptr));

	Droplet* drops = new Droplet[MAXDROPS];
	int ndrops = 0;

	int mx = (RIGHT + LEFT) / 2;
	int my = BOTTOM - 2;

	int fallspeed = 1;
	int delay = 250;
	bool leave = false;

	while (!leave) {
		newDrops(drops, ndrops);
		drawStuff(drops, ndrops, mx, my, leave, fallspeed);
		if (leave) break;
		drawMainCharacter(mx, my);
		handleInput(mx, my, leave);

		gotoxy(0, 0);
		sleep4(delay);
	}
	clearColor();

	delete[] drops;

	return 0;
}