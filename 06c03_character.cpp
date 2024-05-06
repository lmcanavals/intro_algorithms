#include "upc.h"
#include <cctype>
#include <cmath>

using namespace std;

const int DISPLAY_WIDTH = 80;
const int DISPLAY_HEIGHT = 30;
const int LEFT = 10;
const int TOP = 2;

const string TL = "+";
const string TR = "+";
const string BL = "+";
const string BR = "+";
const string HO = "-";
const string VE = "|";

void printxy(int x, int y, string txt) {
  gotoxy(x, y);
  cout << txt;
}

char handleKeys() {
  if (_kbhit()) {
    return toupper(_getch());
  }
  return -1;
}

void drawWindow() {
  color(BRIGHT_RED);
  printxy(LEFT, TOP, TL);
  printxy(DISPLAY_WIDTH + LEFT, TOP, TR);
  printxy(LEFT, DISPLAY_HEIGHT + TOP, BL);
  printxy(DISPLAY_WIDTH + LEFT, DISPLAY_HEIGHT + TOP, BR);
  for (int i = LEFT + 1; i < DISPLAY_WIDTH + LEFT; ++i) {
    printxy(i, TOP, HO);
    printxy(i, DISPLAY_HEIGHT + TOP, HO);
  }
  for (int i = TOP + 1; i < DISPLAY_HEIGHT + TOP; ++i) {
    printxy(LEFT, i, VE);
    printxy(DISPLAY_WIDTH + LEFT, i, VE);
  }
  cout << endl;
  clearColor();
}

bool isPrime(int num) {
  for (int i = 2; i < sqrt(num); ++i) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

bool handleMove(int &x, int &y, char key) {
  printxy(x, y, " ");
  switch (key) {
  case LEFT_KEY: // izquierda
    if (x > LEFT + 1) {
      x -= 1;
    }
    break;
  case RIGHT_KEY: // derecha
    if (x < LEFT + DISPLAY_WIDTH - 1) {
      x += 1;
    }
    break;
  case UP_KEY: // abajo
    if (y > TOP + 1) {
      y -= 1;
    }
    break;
  case DOWN_KEY: // arriba
    if (y < TOP + DISPLAY_HEIGHT - 1) {
      y += 1;
    }
    break;
  }
  printxy(x, y, "*");
  return isPrime(x + y);
}

void handleMoveRandChar(int &x, int &y, bool &active) {
  int vx = randint(1, 100) > 50 ? 1 : -1;
  int vy = randint(1, 100) > 50 ? 1 : -1;

  printxy(x, y, " ");
  x += vx;
  y += vy;
  if (x > LEFT + 1 && x < LEFT + DISPLAY_WIDTH - 1 && y > TOP + 1 &&
      y < TOP + DISPLAY_HEIGHT - 1) {
    printxy(x, y, "@");
    return;
  }
  active = false;
}

int main() {
  clear();
  hideCursor();
  noecho();

  int x = LEFT + DISPLAY_WIDTH / 2;
  int y = TOP + DISPLAY_HEIGHT / 2;
  int rx, ry;
  bool activeRandChar = false;

  drawWindow();
  printxy(x, y, "*");
  bool exit = false;
  while (!exit) {
    char key = handleKeys();
    switch (key) {
    case UP_KEY:
    case DOWN_KEY:
    case RIGHT_KEY:
    case LEFT_KEY:
      if (handleMove(x, y, key) && !activeRandChar) {
        activeRandChar = true;
        rx = x;
        ry = y;
      }
      break;
    case 'X':
      exit = true;
      continue;
    }
    if (activeRandChar) {
      handleMoveRandChar(rx, ry, activeRandChar);
      printxy(x, y, "*");
      if (x == rx && y == ry) {
        printxy(LEFT + DISPLAY_WIDTH / 2 - 4, TOP + DISPLAY_HEIGHT / 2,
                "COLISSION");
        _getch();
        exit = true;
        continue;
      }
    }
    gotoxy(0, 0);
    cout << endl;
    sleep4(100);
  }

  resetAll();
  return 0;
}
