#include "upc.h"

/* no hay necesidad de usar windows.h ni conio.h, son incluidas en upc.h */

using namespace std;

int main() {

	const int left = 10;
	const int right = 39;
	const int top = 5;
	const int bottom = 19;

	int x = left;
	int y = top;
	int dx = 1;
	int dy = 1;

	for (;;) {
		clear();
		hideCursor();
		gotoxy(x, y);
		cout << "hello, world!" << endl;
		x += dx; y += dy;
		if (x < left || x > right) dx *= -1;
		if (y < top || y > bottom) dy *= -1;

		if (_kbhit()) {
			char x = getchar();

			cout << x << x << endl;
			break;
		}
		sleep4(100);
	}
	resetAll();

	return 0;
}
