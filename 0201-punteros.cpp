#include <iostream>

using namespace std;

int main() {
	float x;

	cout << "Ingresa un valor real: ";
	cin >> x;

	cout << "El valor ingresado es: " << x << endl;

	float *ptr;

	ptr = &x; // & se usa como operador de dirección, obtiene la dirección de x

	cout << "Dirección? " << ptr << endl;

	*ptr = 40.5; // * se usa como operador de indirección, accede y modifica x a través del puntero ptr

	cout << "NUevo valor de X: " << x << endl;

	return 0;
}
