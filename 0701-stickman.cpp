#include "upc.h"

using namespace std;

void drawStickMan(int x, int y) {
  gotoxy(x, y);
  cout << "  O";
  gotoxy(x, y + 1);
  cout << "-- --";
  gotoxy(x, y + 2);
  cout << "  |";
  gotoxy(x, y + 3);
  cout << " / \\";
}

int main() {
  int *x = new int;
  int *y = new int;
  int *dx = new int;
  int *dy = new int;
  const int delay = 50;
  const int right = 115;
  const int left = 0;
  const int top = 0;
  const int bottom = 26;

  *x = left;
  *y = top;
  *dx = 1;
  *dy = 0;

  for (;;) { // bucle infinito
		if (_kbhit()) {
			break;
		}
    clear();
    drawStickMan(*x, *y);
    *x += *dx;
    *y += *dy;

    if (*x == right) {
      *dx = 0;
      *dy = 1;
      *x = right - 1;
    } else if (*y == bottom) {
      *dx = -1;
      *dy = 0;
      *y = bottom - 1;
    } else if (*x == left - 1) {
      *dx = 0;
      *dy = -1;
      *x = left;
    } else if (*y == top - 1) {
      *dx = 1;
      *dy = 0;
      *y = top;
    }

    cout << endl;
    sleep4(delay);
  }

  delete x;
  delete y;
  delete dx;
  delete dy;

  return 0;
}
