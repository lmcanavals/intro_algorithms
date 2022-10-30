/* #ifndef es la forma estandard de declarar un h, #pragma no funciona en gcc */
#ifndef __UPC_H__
#define __UPC_H__

/* includes generales */
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>

#include <stdio.h>


/*************************************
 * validación
 * **********************************/

 /* validar si string es un entero [+\-]?\d+ */
bool isInt(std::string str) {
	bool digits = false;
	for (unsigned int i = 0; i < str.size(); ++i) {
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
bool isFloat(std::string str) {
	bool digits = false;
	bool dot = false;
	for (unsigned int i = 0; i < str.size(); ++i) {
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
int readInt(std::string msg) {
	std::string str;
	do {
		std::cout << msg; getline(std::cin, str);
		if (!isInt(str)) {
			std::cout << "<" << str << "> no es un número entero.\n";
		}
	} while (!isInt(str));
	return stoi(str);
}

/* validación un poco fea de float */
float readFloat(std::string msg) {
	std::string str;
	do {
		std::cout << msg; getline(std::cin, str);
		if (!isFloat(str)) {
			std::cout << "<" << str << "> no es un número real.\n";
		}
	} while (!isFloat(str));
	return stof(str);
}

/* validando feamente un rango entero */
int readIntRange(std::string msg, int min, int max) {
	int num;
	do {
		num = readInt(msg);
		if (num < min || num > max) {
			std::cout << "<" << num << "> no está en el rango ["
				<< min << ".." << max << "]\n";
		}
	} while (num < min || num > max);
	return num;
}

/* validación de rango real */
float readFloatRange(std::string msg, float min, float max) {
	float num;
	do {
		num = readFloat(msg);
		if (num < min || num > max) {
			std::cout << "<" << num << "> no está en el rango ["
				<< min << ".." << max << "]\n";
		}
	} while (num < min || num > max);
	return num;
}

/**
* generar número aleatorio entre a y b, [a, b> sin incluir b.
*/
int randint(int a, int b) {
	return rand() % (b - a) + a;
}

struct ConsoleInfo {
	int numColumns;
	int numRows;
	int bottom;
	int left;
	int right;
	int top;
	int boxRows;
	int boxCols;
};

int randColor() {
	return rand() % 16;
}

/*************************************
 * elementos condicionales al sistema operativo
 * **********************************/

#ifdef _WIN32

 /* si se compila en windows, intenta usar windows.h */
#include <windows.h>
#include <conio.h>

enum Colors {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_CYAN,
	DARK_RED,
	DARK_MAGENTA,
	DARK_YELLOW,
	DARK_WHITE,
	BRIGHT_BLACK,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_MAGENTA,
	BRIGHT_YELLOW,
	WHITE
};

/* dormir (detener) proceso por x milisegundos */
void sleep4(int milliseconds) {
	Sleep(milliseconds);
}

/* limpiar pantalla */
void clear() {
	system("cls");
}

/* saltar a una posición x, y en la pantalla */
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void background(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color << 4);
}

void foreground(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

void clearColor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 7);
}

/* utilice solo esta funcion */
void color(int forecolor, int backcolor = BLACK) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, backcolor << 4 | forecolor);
}

void getConsoleInfo(ConsoleInfo* ci, int mt=0, int mr=0, int mb=0, int ml=0) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	ci->numColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	ci->numRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	ci->top = csbi.srWindow.Top + mt;
	ci->right = csbi.srWindow.Right - mr;
	ci->bottom = csbi.srWindow.Bottom - mb;
	ci->left = csbi.srWindow.Left + ml;
	ci->boxRows = ci->bottom - ci->top + 1;
	ci->boxCols = ci->right - ci->left + 1;
}

void HideCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
}

/* else del bloque _WIN32 */
#else

 /* para gcc, macos, *nix se usa en su lugar, ncurses y unistd */
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>

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

/* dormir (detener) proceso por x milisegundos */
void sleep4(int milliseconds) {
	usleep(milliseconds * 1000);
}

/* limpiar pantalla */
void clear() {
	system("clear");
}

/* saltar a una posición x, y en la pantalla */
void gotoxy(int x, int y) {
	printf("%c[%d;%df", 0x1B, y + 1, x + 1);
}

void clearColor() {
	printf("\033[0m");
}

void background(int color) {
	if (color < 8) {
		printf("\033[4%dm", color);
	} else {
		printf("\033[0;10%dm", color % 8);
	}
}

void foreground(int color) {
	int bold = color / 8;
	printf("\033[%d;3%dm", bold, color % 8);
}

/* utilice solo esta funcion */
void color(int forecolor, int backcolor = -1) {
	if (backcolor == -1) {
		printf("\033[38;5;%dm", forecolor);
	} else {
		printf("\033[38;5;%dm\033[48;5;%dm", forecolor, backcolor);
	}
}

void getConsoleInfo(ConsoleInfo* ci, int mt=0, int mr=0, int mb=0, int ml=0) {
	winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	ci->numColumns = size.ws_col;
	ci->numRows = size.ws_row;
	ci->top = mt;
	ci->right = ci->numColumns - mr - 1;
	ci->bottom = ci->numRows - mb - 1;
	ci->left = ml;
	ci->boxRows = ci->bottom - ci->top + 1;
	ci->boxCols = ci->right - ci->left + 1;
}

void hideCursor() {
	printf("\033[?25l");
}

void showCursor() {
	printf("\033[?25h");
}

/* detección de tecla presionada para linux
 * gracias a Morgan Mattews
 * https://www.flipcode.com/archives/_kbhit_for_Linux.shtml */
int _kbhit() {
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

int _getch() {
	return getchar();
}

void noecho() {
	struct termios t;
	if (tcgetattr(STDIN_FILENO, &t) == -1) return;
	t.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
void echo() {
	struct termios t;
	if (tcgetattr(STDIN_FILENO, &t) == -1) return;
	t.c_lflag |= (ECHO | ECHOE | ECHOK | ECHONL);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

/* endif del bloque _WIN32 (else) */
#endif

void resetAll() {
	clearColor();
	clear();
	showCursor();
	echo();
}

#endif
