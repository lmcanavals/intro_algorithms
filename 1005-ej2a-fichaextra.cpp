#include <stdlib.h>
#include <iomanip>

#include "upc.h"

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

Figure* randFigure(ConsoleInfo* ci) {
	Figure* fig = new Figure;
	fig->color = randColor();
	fig->ch = '*';
	fig->h = 1;
	fig->w = randint(2, 10);
	fig->x = randint(ci->left + 1, ci->right - fig->w - 1);
	fig->y = randint(ci->top + 1, ci->bottom - fig->h - 1);
	fig->dx = randint(1, 3) * (randint(0, 2) == 0? -1 : 1);
	fig->dy = randint(1, 3) * (randint(0, 2) == 0 ? -1 : 1);

	return fig;
}

void drawFigure(Figure* fig, ConsoleInfo* ci) {
	color(fig->color);
	int cols = ci->right - ci->left + 1;
	int rows = ci->bottom - ci->top + 1;
	for (int i = 0; i < fig->h; ++i) {
		gotoxy(fig->x, fig->y + i);
		for (int j = 0; j < fig->w; ++j) {
			gotoxy(fig->x, fig->y + i);
			cout << fig->ch;
		}
	}
	clearColor();
}

void updateFigure(Figure* fig, ConsoleInfo* ci) {
	fig->x += fig->dx;
	fig->y += fig->dy;
	if (fig->dx > 0 && fig->x + fig->w >= ci->right) {
		fig->x = ci->left;
	} else if (fig->dx < 0 && fig->x <= ci->left) {
		fig->x = ci->right;
	}
	if (fig->dy > 0 && fig->y + fig->h >= ci->bottom) {
		fig->y = ci->top;
	} else if (fig->dy < 0 && fig->y <= ci->top) {
		fig->y = ci->bottom;
	}
}

int main() {
	srand(time(nullptr));
	ConsoleInfo* ci = new ConsoleInfo;
	getConsoleInfo(ci, 2, 30, 2, 30);

	int n = randint(5, 11);
	Figure** fig = new Figure*[n];

	for (int i = 0; i < n; ++i) {
		fig[i] = randFigure(ci);
	}

	HideCursor();
	for (;;) {
		clear();
		for (int i = 0; i < n; ++i) {
			drawFigure(fig[i]);
			updateFigure(fig[i], ci);
		}
		sleep4(100);
	}

	for (int i = 0; i < n; ++i) {
		delete fig[i];
	}
	delete[] fig;
	delete ci;

	return 0;
}
