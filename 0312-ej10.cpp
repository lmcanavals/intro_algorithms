#include <iostream>

using namespace std;

void calcularDescuento(float monto, float& descuento) {
	float pctje = (monto >= 10000) * 0.2 + (monto < 10000) * 0.1;
	descuento = monto*pctje;
}

int main() {
	float monto, descuentoFinal;

	cout << "Ingrese el monto: ";
	cin >> monto;

	calcularDescuento(monto, descuentoFinal);

	cout << "El descuento es: " << descuentoFinal << endl;

	return 0;
}


