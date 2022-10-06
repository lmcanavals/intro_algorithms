#include "upc.h"

using namespace std;

/* w: ancho
 * h: alto
 * s: espaciado
 **/
void hacerFigura(int w, int h, int s) {
	for (int j = 1; j <= h; ++j) {
		int cont = 0;
		for (int i = 1; i <= w; ++i) {
			if (j == 1 || j == h || cont == 0) {
				cout << (i % 10) << " ";
			} else {
				cout << "  ";
			}
			cont = ++cont % s;
		}
		cout << endl;
	}
}

int main() {
	int* ancho = new int;
	int* altura = new int;
	int* espaciado = new int;

	*ancho = readIntRange("Ingrese Ancho [1..51]: ", 1, 51);
	*altura = readIntRange("Ingrese Alto [1..17]: ", 1, 17);
	*espaciado = readIntRange("Ingrese espaciado [1..Alto]: ", 1, *altura);

	hacerFigura(*ancho, *altura, *espaciado);

	delete ancho;
	delete altura;
	delete espaciado;

	return 0;
}
