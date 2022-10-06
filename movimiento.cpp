#include "upc.h"

#define SHIP 'H'
#define BULLET '*'

using namespace std;

/* esta función borra el caracter en la última posición conocida (lastx, lasty)
 * y dibuja el character en la nueva posición (x, y), esto evita el 
 * parpadeo excesivo
 **/
void smartprint(char ch, int* x, int* y, int* lastx, int* lasty) {
		gotoxy(*lastx, *lasty); cout << ' ' << endl;
		gotoxy(*x, *y); cout << ch << endl;
		*lastx = *x;
		*lasty = *y;
}

int main() {

	// limites de nuestra pantalla
	const int left = 5;
	const int right = 74;
	const int top = 1;
	const int bottom = 24;

  // posicion para la nave, controlados manualmente
	int* x = new int;
	int* y = new int;
	int* lastx = new int;
	int* lasty = new int;

	// posicion para la balita, controlado automáticamente
	int* xb = new int;
	int* yb = new int;
	int* lastxb = new int;
	int* lastyb = new int;

	// velocidad de la balita
	int* dyb = new int;
	
	// otras variables
	char* key = new char;
	bool* leave = new bool;
	bool* shooted = new bool;

	*lastx = *x = (left + right) / 2;
	*lasty = *y = bottom;
	*leave = false;

	*shooted = false;
	*dyb = -1;

	clear();
	while (!*leave) {
		sleep4(100); // una pausa de 100 ms, sino, se puede colgar...
		smartprint(SHIP, x, y, lastx, lasty);
		if (*shooted) { // si se disparó, dibujar y actualizar posición de la bala
			smartprint(BULLET, xb, yb, lastxb, lastyb);
			*yb += *dyb;
			if (*yb == top) {
				*shooted = false;
				smartprint(' ', lastxb, lastyb, lastxb, lastyb);
			}
		}
		if (_kbhit()) { // si se detecta tecla presionada, procesarla.
			*key = _getch();
			*key = tolower(*key);
			switch (*key) {
			case 'a': // en caso de mover a la izquierda, no pasará del limite left
				if (*x > left) {
					--*x;
				}
				break;
			case 'd': // lo mismo para la derecha
				if (*x < right) {
					++*x;
				}
				break;
			case ' ': // barra espaciadora, producir nueva bala si no hay una ahora.
				if (!*shooted) {
					*shooted = true;
					*lastxb = *xb = *x;
					*lastyb = *yb = *y - 1;
				}
				break;
			case 'x': // saliendo
				*leave = true;
				break;
			}
		}

	}
	clear();

	// limpiando la casa
	delete x;
	delete y;
	delete lastx;
	delete lasty;
	delete xb;
	delete yb;
	delete lastxb;
	delete lastyb;
	delete dyb;
	delete key;
	delete leave;
	delete shooted;

	return 0;
}
