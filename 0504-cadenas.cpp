#include <iostream>
#include <string>

using namespace std;

int main() {
	string cadena;

	cout << "Ingresa una cadena: ";
	getline(cin, cadena);

	cout << "La cadena ingresada es << " << cadena << " >>\n";

	do {
		cout << "Ingresa otra cadena: "; cin >> cadena;
		cout << "Usted ha ingresado << " << cadena << " >>\n";
	} while (cadena != "fin"); cin.get();

	cout << "Una ultima cadenita por favor: "; getline(cin, cadena);

	int i = 0;
	while (i < cadena.size()) {
		cout << "cadena[" << i << "] = " << cadena[i]
			 << "(" << (int)cadena[i] << ")" << endl;
		i++;
	}

	return 0;
}