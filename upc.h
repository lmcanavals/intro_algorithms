/* #ifndef es la forma estandard de declarar un h, #pragma no funciona en gcc */
#ifndef __UPC_H__
#define __UPC_H__

/* includes generales */
#include <iostream>
#include <string>

#include <stdio.h>


/*************************************
 * validación
 * **********************************/

/* validar si string es un entero [+\-]?\d+ */
bool isInt(std::string str) {
	bool digits = false;
	for (int i = 0; i < str.size(); ++i) {
		if (i == 0 && str[i] == '-' || str[i] == '+') {
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
	for (int i = 0; i < str.size(); ++i) {
		if (i == 0 && str[i] == '-' || str[i] == '+') {
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

/*************************************
 * elementos condicionales al sistema operativo
 * **********************************/

#ifdef _WIN32

/* si se compila en windows, intenta usar windows.h */
#include <windows.h>
#include <conio.h>

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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),  coord);
}

/* else del bloque _WIN32 */
#else

/* para gcc, macos, *nix se usa en su lugar, ncurses y unistd */
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>

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
	printf("%c[%d;%df", 0x1B, y, x);
}

/* detección de tecla presionada para linux
 * gracias a Morgan Mattews
 * https://www.flipcode.com/archives/_kbhit_for_Linux.shtml */
int _kbhit() {
	static const int STDIN = 0;
	static bool initialized = false;

	if (! initialized) {
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

/* endif del bloque _WIN32 (else) */
#endif

#endif
