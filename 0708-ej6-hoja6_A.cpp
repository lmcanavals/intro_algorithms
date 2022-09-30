#include <math.h>
#include "upc.h"

using namespace std;


/* transformar del rango -1.4..1.5 => 0..29 */
int scaleY(float y, float factor) {
	return 30 - (int) ((y + 1.5) * factor);
}
float scaleXinv(int x) {
	return x / 2.5;
}

int main() {
	int y;
	float factor = 7;
	char key;

	do {
		clear();
		for (int x = 0; x < 119; ++x) {
			y = scaleY(sin(scaleXinv(x)), factor);
			gotoxy(x, y);
			cout << "*" << endl;
		}
		key = _getch();
		if (key == '+') {
			++factor;
		} else if (key == '-') {
			--factor;
		}
	}	while (key != 'x');

	gotoxy(0, 30);

	return 0;
}
