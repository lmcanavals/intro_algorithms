#include <iostream>
#include <conio.h>

#include "upc.h"

using namespace std;


char menu() {
	char op;
	system("cls || clear");
	cout << "Dibujar una figura\n"
		<< "------------------\n"
		<< "[1] Cuadrado\n"
		<< "[2] Triángulo\n"
		<< "[0] Salir\n"
		<< "Elija una opción: ";
	cin >> op;
	return op;
}

void spaces(int n) {
	for (int i = 0; i < n; ++i) {
		cout << " ";
	}
}

void cuadrado() {
	int* n = new int;

	*n = readInt("Ingrese un número n [4..6]: ");

	for (int i = 1; i <= *n; ++i) {
		spaces(i * 4); cout << "****\n";
		spaces(i * 4); cout << "*" << i << " *\n";
		spaces(i * 4); cout << "*  *\n";
		spaces(i * 4); cout << "****\n";
	}

	delete n;
}

void triangulo() {
	int* n = new int;

	*n = readInt("Ingrese un número n [4..6]: ");

	for (int i = 1; i <= *n; ++i) {
		spaces(i * 4); cout << "  *\n";
		spaces(i * 4); cout << " *" << i << "*\n";
		spaces(i * 4); cout << "*****\n";
	}

	delete n;
}

int main() {
	char op;
	do {
		op = menu();
		switch (op) {
		case '1':
			cuadrado();
			break;
		case '2':
			triangulo();
			break;
		case '0':
			system("cls || clear");
			cout << "Eso es todo amigos...\n";
		default:
			cout << "<" << op << "> no es una opción válida.\n";
		}
		cout << "Presione <enter> para continuar...\n";
		_getch();
	} while (op != '0');

	return 0;
}