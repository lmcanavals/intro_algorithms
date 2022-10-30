#include "upc.h"

#define TOP 2
#define RIGHT 89
#define BOTTOM 22
#define LEFT 10

#define DROPCHANCE 10
#define MAXDROPS 201

using namespace std;

char** newMatrix(int rows, int cols) {
	char** mat = new char*[rows];
	for (int i = 0; i < rows; ++i) {
		mat[i] = new char[cols];
		for (int j = 0; j < cols; ++j) {
			if (randint(1, 101) <= 5) {
				mat[i][j] = (char)randint('0', '9' + 1);
			} else {
				mat[i][j] = ' ';
			}
		}
	}
	return mat;
}

void deleteMat(char** mat, int rows) {
	for (int i = 0; i < rows; ++i) {
		delete[] mat[i];
	}
	delete[] mat;
}

struct World {
	char** buffer;
	int rows;
	int cols;
};

void drawWorld(World* w, ConsoleInfo* ci) {
	clear();
	for (int i = 0; i < w->rows; ++i) {
		gotoxy(ci->left, ci->top + i);
		for (int j = 0; j < w->cols; ++j) {
			cout << w->buffer[i][j];
		}
	}
}

void updateBuffer(World* w) {
	for (int i = 0; i < w->rows; ++i) {
		char temp = w->buffer[i][0];
		for (int j = 0; j < w->cols - 1; ++j) {
			w->buffer[i][j] = w->buffer[i][j + 1];
		}
		w->buffer[i][w->cols - 1] = temp;
	}
}

int main() {
	ConsoleInfo* ci = new ConsoleInfo;
	getConsoleInfo(ci, 2, 30, 2, 30);

	cout << ci->numColumns << endl;
	cout << ci->numRows << endl;

	World* w = new World;
	w->rows = ci->bottom - ci->top + 1;
	w->cols = ci->right - ci->left + 1;
	w->buffer = newMatrix(w->rows, w->cols);

	for (;;) {
		drawWorld(w, ci);
		updateBuffer(w);
		sleep4(100);
		if (_kbhit()) {
			char op = _getch();
			if (op == 'x') break;
		}
	}

	deleteMat(w->buffer, w->rows);
	delete w;

	return 0;
}
