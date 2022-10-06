#include "upc.h"

#define SHIP 'H'
#define BULLET '*'

using namespace std;

void smartprint(char ch, int* x, int* y, int* lastx, int* lasty) {
		gotoxy(*lastx, *lasty); cout << ' ' << endl;
		gotoxy(*x, *y); cout << SHIP << endl;
		*lastx = *x;
		*lasty = *y;
}

int main() {

	const int left = 5;
	const int right = 74;
	const int top = 1;
	const int bottom = 24;

	int* x = new int; // posicion para la nave, controlados manualmente
	int* y = new int;
	int* lastx = new int;
	int* lasty = new int;

	int* xb = new int; // posicion para la balita, controlado automáticamente
	int* yb = new int;

	int* dyb = new int; // velocidad de la balita
	
	char* key = new char;
	bool* exit = new bool;

	*lastx = *x = (left + right) / 2;
	*lasty = *y = bottom;
	*exit = false;

	clear();
	while (!*exit) {
		sleep4(100);
		smartprint(SHIP, x, y, lastx, lasty);
		if (_kbhit()) {
			*key = _getch();
			*key = tolower(*key);
			switch (*key) {
			case 'a':
				if (*x > left) {
					--*x;
				}
				break;
			case 'd':
				if (*x < right) {
					++*x;
				}
				break;
			case 'x':
				*exit = true;
				break;
			}
		}

	}
	clear();

	delete x;
	delete y;
	delete lastx;
	delete lasty;
	delete xb;
	delete yb;
	delete dyb;
	delete key;

	return 0;
}
