#include <stdlib.h>
#include <iomanip>

#include "upc.h"

#define LEFT 30
#define TOP 2
#define RIGHT 90
#define BOTTOM 28

using namespace std;

struct Figure {
	int x;
	int y;
	int color;
	char ch; // caracter a imprimir
	int w; // ancho
	int h; // alto
	int dx;
	int dy;
};

Figure* randFigure() {
	Figure* fig = new Figure;
	fig->color = randColor();
	fig->ch = '*';
	fig->h = 1;
	fig->w = randint(2, 10);
	fig->x = randint(LEFT + 1, RIGHT - fig->w - 1);
	fig->y = randint(TOP + 1, BOTTOM - fig->h - 1);
	fig->dx = randint(1, 3) * (randint(0, 2) == 0? -1 : 1);
	fig->dy = randint(1, 3) * (randint(0, 2) == 0 ? -1 : 1);

	return fig;
}

void drawFigure(Figure* fig) {
	color(fig->color);
	for (int i = 0; i < fig->h; ++i) {
		gotoxy(fig->x, fig->y + i);
		for (int j = 0; j < fig->w; ++j) {
			cout << fig->ch;
		}
	}
	clearColor();
	gotoxy(0, 0);
}

void updateFigure(Figure* fig) {
	fig->x += fig->dx;
	fig->y += fig->dy;
	if (fig->x <= LEFT || fig->x + fig->w > RIGHT) {
		fig->dx *= -1;
	}
	if (fig->y <= TOP || fig->y + fig->h > BOTTOM) {
		fig->dy *= -1;
	}
}

int main() {
	srand(time(nullptr));
	int n = randint(5, 11);
	Figure** fig = new Figure*[n];

	for (int i = 0; i < n; ++i) {
		fig[i] = randFigure();
	}

	for (;;) {
		clear();
		for (int i = 0; i < n; ++i) {
			drawFigure(fig[i]);
			updateFigure(fig[i]);
		}
		sleep4(100);
	}

	for (int i = 0; i < n; ++i) {
		delete fig[i];
	}
	delete[] fig;

	return 0;
}
