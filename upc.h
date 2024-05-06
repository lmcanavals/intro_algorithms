/* #ifndef es la forma estandard de declarar un h, #pragma no funciona en gcc */
#ifndef __UPC_H__
#define __UPC_H__

/* includes generales */
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>

#include <stdio.h>

/*************************************
 * validación
 * **********************************/

/* validar si string es un entero [+\-]?\d+ */
inline bool isInt(std::string str) {
  bool digits = false;
  for (uint32_t i = 0; i < str.size(); ++i) {
    if (i == 0 && (str[i] == '-' || str[i] == '+')) {
      continue;
    } else if (str[i] >= '0' && str[i] <= '9') {
      digits = true;
    } else {
      return false;
    }
  }
  return digits;
}

/* validar si std::string es float forma simple [+\-]?\d+\.\d+ */
inline bool isFloat(std::string str) {
  bool digits = false;
  bool dot = false;
  for (uint32_t i = 0; i < str.size(); ++i) {
    if (i == 0 && (str[i] == '-' || str[i] == '+')) {
      continue;
    } else if (str[i] >= '0' && str[i] <= '9') {
      digits = true;
    } else if (str[i] == '.') {
      if (dot || !digits) {
        return false;
      } else {
        dot = true;
        digits = false;
      }
    }
  }
  return digits;
}

/* validación no muy elegante de entero */
inline int readInt(std::string msg) {
  std::string str;
  do {
    std::cout << msg;
    getline(std::cin, str);
    if (!isInt(str)) {
      std::cout << "<" << str << "> no es un número entero.\n";
    }
  } while (!isInt(str));
  return stoi(str);
}

/* validación un poco fea de float */
inline float readFloat(std::string msg) {
  std::string str;
  do {
    std::cout << msg;
    getline(std::cin, str);
    if (!isFloat(str)) {
      std::cout << "<" << str << "> no es un número real.\n";
    }
  } while (!isFloat(str));
  return stof(str);
}
inline double readDouble(std::string msg) {
  std::string str;
  do {
    std::cout << msg;
    getline(std::cin, str);
    if (!isFloat(str)) {
      std::cout << "<" << str << "> no es un número real.\n";
    }
  } while (!isFloat(str));
  return std::stod(str);
}

/* validando feamente un rango entero */
inline int readIntRange(std::string msg, int min, int max) {
  int num;
  do {
    num = readInt(msg);
    if (num < min || num > max) {
      std::cout << "<" << num << "> no está en el rango [" << min << ".." << max
                << "]\n";
    }
  } while (num < min || num > max);
  return num;
}

/* validación de rango real */
inline float readFloatRange(std::string msg, float min, float max) {
  float num;
  do {
    num = readFloat(msg);
    if (num < min || num > max) {
      std::cout << "<" << num << "> no está en el rango [" << min << ".." << max
                << "]\n";
    }
  } while (num < min || num > max);
  return num;
}
inline double readDoubleRange(std::string msg, double min, double max) {
  double num;
  do {
    num = readDouble(msg);
    if (num < min || num > max) {
      std::cout << "<" << num << "> no está en el rango [" << min << ".." << max
                << "]\n";
    }
  } while (num < min || num > max);
  return num;
}

/**
 * generar número aleatorio entre a y b, [a, b> sin incluir b.
 */
inline int randint(int a, int b, std::random_device rd = std::random_device()) {
  std::mt19937_64 gen(rd());
  return gen() % (b - a) + a;
}

struct ConsoleInfo {
  int maxColumns;
  int maxRows;
  int bottom;
  int left;
  int right;
  int top;
  int boxRows;
  int boxCols;
};

inline int randColor() { return rand() % 16; }

enum Colors {
  BLACK,
  DARK_RED,
  DARK_GREEN,
  DARK_YELLOW,
  DARK_BLUE,
  DARK_MAGENTA,
  DARK_CYAN,
  DARK_WHITE,
  BRIGHT_BLACK,
  BRIGHT_RED,
  BRIGHT_GREEN,
  BRIGHT_YELLOW,
  BRIGHT_BLUE,
  BRIGHT_MAGENTA,
  BRIGHT_CYAN,
  WHITE
};

/*************************************
 * elementos condicionales al sistema operativo
 * **********************************/

#ifdef _WIN32

/* si se compila en windows, intenta usar windows.h */
#include <conio.h>
#include <windows.h>

#define UP_KEY 82
#define DOWN_KEY 80
#define RIGHT_KEY 77
#define LEFT_KEY 75

int __WINCOLOR__[] = {0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15};

/* dormir (detener) proceso por x milisegundos */
inline void sleep4(int milliseconds) { Sleep(milliseconds); }

/* limpiar pantalla */
inline void clear() { system("cls"); }

/* saltar a una posición x, y en la pantalla */
inline void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline void background(int color) {
  color = __WINCOLOR__[color];
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, color << 4);
}

inline void foreground(int color) {
  color = __WINCOLOR__[color];
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, color);
}

inline void clearColor() {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, 7);
}

/* utilice solo esta funcion */
inline void color(int forecolor, int backcolor = BLACK) {
  forecolor = __WINCOLOR__[forecolor];
  backcolor = __WINCOLOR__[backcolor];
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, backcolor << 4 | forecolor);
}

inline void getConsoleInfo(ConsoleInfo *ci, int mt = 0, int mr = 0, int mb = 0,
                           int ml = 0) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  ci->maxColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  ci->maxRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  ci->top = csbi.srWindow.Top + mt;
  ci->right = csbi.srWindow.Right - mr;
  ci->bottom = csbi.srWindow.Bottom - mb;
  ci->left = csbi.srWindow.Left + ml;
  ci->boxRows = ci->bottom - ci->top + 1;
  ci->boxCols = ci->right - ci->left + 1;
}

inline void hideCursor() {
  HANDLE hCon;
  hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  cci.dwSize = 2;
  cci.bVisible = FALSE;
  SetConsoleCursorInfo(hCon, &cci);
}

inline void showCursor() {
  HANDLE hCon;
  hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  cci.dwSize = 2;
  cci.bVisible = TRUE;
  SetConsoleCursorInfo(hCon, &cci);
}

inline void noecho() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
}
inline void echo() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & (ENABLE_ECHO_INPUT));
}

/* else del bloque _WIN32 */
#else

/* para gcc, macos, *nix se usa en su lugar, ncurses y unistd */
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

#define UP_KEY 'A'
#define DOWN_KEY 'B'
#define RIGHT_KEY 'C'
#define LEFT_KEY 'D'

/* dormir (detener) proceso por x milisegundos */
inline void sleep4(int milliseconds) { usleep(milliseconds * 1000); }

/* limpiar pantalla */
inline void clear() { system("clear"); }

/* saltar a una posición x, y en la pantalla */
inline void gotoxy(int x, int y) { printf("%c[%d;%df", 0x1B, y + 1, x + 1); }

inline void clearColor() { printf("\033[0m"); }

inline void background(int color) {
  if (color < 8) {
    printf("\033[4%dm", color);
  } else {
    printf("\033[0;10%dm", color % 8);
  }
}

inline void foreground(int color) {
  int bold = color / 8;
  printf("\033[%d;3%dm", bold, color % 8);
}

/* utilice solo esta funcion */
inline void color(int forecolor, int backcolor = -1) {
  if (backcolor == -1) {
    printf("\033[38;5;%dm", forecolor);
  } else {
    printf("\033[38;5;%dm\033[48;5;%dm", forecolor, backcolor);
  }
}

inline void getConsoleInfo(ConsoleInfo *ci, int mt = 0, int mr = 0, int mb = 0,
                           int ml = 0) {
  winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  ci->maxColumns = size.ws_col;
  ci->maxRows = size.ws_row;
  ci->top = mt;
  ci->right = ci->maxColumns - mr - 1;
  ci->bottom = ci->maxRows - mb - 1;
  ci->left = ml;
  ci->boxRows = ci->bottom - ci->top + 1;
  ci->boxCols = ci->right - ci->left + 1;
}

inline void hideCursor() { printf("\033[?25l"); }

inline void showCursor() { printf("\033[?25h"); }

/* detección de tecla presionada para linux
 * gracias a Morgan Mattews
 * https://www.flipcode.com/archives/_kbhit_for_Linux.shtml */
inline int _kbhit() {
  static const int STDIN = 0;
  static bool initialized = false;

  if (!initialized) {
    // Use termios to turn off line buffering
    termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = true;
  }

  int bytesWaiting;
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}

inline int _getch() { return getchar(); }

inline void noecho() {
  struct termios t;
  if (tcgetattr(STDIN_FILENO, &t) == -1)
    return;
  t.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
inline void echo() {
  struct termios t;
  if (tcgetattr(STDIN_FILENO, &t) == -1)
    return;
  t.c_lflag |= (ECHO | ECHOE | ECHOK | ECHONL);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

/* endif del bloque _WIN32 (else) */
#endif

inline void resetAll() {
  clearColor();
  clear();
  showCursor();
  echo();
}

#endif
