#include <iostream>
#include <ctype.h>

/* ctype.h para la función toupper() que convierte a mayúscula
*/

using namespace std;

void leerDatos(char*, char*, int*);
float calcularPctjDscto(char*, int*);
float calcularPU(char*);

int main() {
	char*  zona = new char;
	char*  socio = new char;
	int*   nroEntradas = new int;
	float* precioUnitario = new float;
	float* subtotal = new float;
	float* precioFinal = new float;
	float* pctjDscto = new float;
	float* descuento = new float;

	leerDatos(zona, socio, nroEntradas);
	
	*pctjDscto 			= calcularPctjDscto(socio, nroEntradas);
	*precioUnitario = calcularPU(zona);
	*subtotal 			= *precioUnitario * *nroEntradas;
	*descuento 			= *subtotal * *pctjDscto;
	*precioFinal 		= *subtotal - *descuento;

	cout << "El monto a pagar es: " << *precioFinal << endl;
	
	delete zona;
	delete socio;
	delete nroEntradas;
	delete precioUnitario;
	delete subtotal;
	delete precioFinal;
	delete pctjDscto;
	delete descuento;

	return 0;
}

void leerDatos(char* zona, char* socio, int* nroEntradas) {
	cout << "Ingrese la zona elegida ([V] Vip, [P] Platea, [E] Popular): ";
	cin >> *zona;
	cout << "Ingrese el número de entradas: ";
	cin >> *nroEntradas;
	cout << "Es socio de la U (S: sí; N: no): ";
	cin >> *socio;
	*zona = toupper(*zona);
	*socio = toupper(*socio);
}

float calcularPctjDscto(char* socio, int* nroEntradas) {
	float pctjDscto;

	pctjDscto  = (*nroEntradas >= 3 && *nroEntradas <= 6) * 0.05;
	pctjDscto += (*nroEntradas >= 7 && *nroEntradas <= 9) * 0.075;
	pctjDscto += (*nroEntradas > 9) * 0.1;

	pctjDscto += (*socio == 'S') * 0.08;

	return pctjDscto;
}

float calcularPU(char* zona) {
	float precioUnitario;

	precioUnitario  = (*zona == 'V') * 350.0;
	precioUnitario += (*zona == 'P') * 130.0;
	precioUnitario += (*zona == 'E') *  50.0;

	return precioUnitario;
}