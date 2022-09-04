#include <iostream>
#include <math.h>

using namespace std;

float* elevarAlCubo(float* n) {
	float* cubo = new float;

	*cubo = pow(*n, 3);

	return cubo;
}

int main() {
	float* numero = new float;

	cout << "Ingrese un número: ";
	cin >> *numero;

	float* cubo = elevarAlCubo(numero);

	cout << *numero << " al cubo es " << *cubo << endl;

	delete numero;
	delete cubo;

	return 0;
}
