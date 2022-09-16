#include <iostream>

using namespace std;

int main() {
	int num;

	do {
		cout << "Ingresa un número mayor a 10: "; cin >> num;
		if (num <= 10) {
			cerr << num << " no es mayor que 10.\n";
			// cout << "hola\n"; es lo mismo que cout << "hola" << endl;
		}
	} while (num <= 10);
	cout << "Felicitaciones, ingresaste el dato correctamente.\n";

	return 0;
}