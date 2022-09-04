#include <iostream>

using namespace std;

int* escogerMayor(int* a, int* b, int* c);

int main() {
	int* a = new int;
	int* b = new int;
	int* c = new int;

	cout << "Ingrese los valores para a, b, y c (separados por espacio): ";
	cin >> *a >> *b >> *c;

	int* mayor = escogerMayor(a, b, c);

	cout << "El mayor es: " << *mayor << endl;

	delete a;
	delete b;
	delete c;
	delete mayor;

	return 0;
}

int* escogerMayor(int* a, int* b, int* c) {
	int* mayor = new int;

	*mayor  = (*a >= *b && *a >= *c) * *a;
	*mayor += (*b > *a && *b >= *c)  * *b;
	*mayor += (*c > *a && *c > *b)  * *c;

	return mayor;
}

