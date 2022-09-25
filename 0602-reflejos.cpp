#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main() {

	char ch;

	cout << "--------------------------------\n"
		<< "PROGRAMA PARA MEDIR LOS REFLEJOS\n"
		<< "--------------------------------\n";

	cout << "Ingrese un caracter: "; cin >> ch;

	cout << "Ahora debes estar atento!\n"
		<< "-------------------------\n";

	int speed = 5; // veces por segundo que aparecerá el caracter;
	
	int numPrints = 0;
	for (;;) {
		++numPrints;
		cout << ch;
		Sleep(1000 / speed);
		if (_kbhit()) {
			_getch();
			cout << "\nSu reflejo despues de " << numPrints << " impresiones.\n";
			numPrints = 0;
			++speed;
		}
	}

	return 0;
}