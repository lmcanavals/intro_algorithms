#include <iostream>
#include <string>

using namespace std;

/*
 * Declaración de una función:
 *	<Tipo retorno> <Nombre función>([lista tipos de datos de parámetros]);
 *
 * Implementación de función:
 *	<Tipo retorno> <Nombre función>([lista de tipos y parámetros]) {
 *		<cuerpo de la función>
 *		return valor; // solo en caso de función de tipo distinto a void.
 *	}
 *
 **/

// procedimiento: es de tipo void y no retorna nada
void procedimiento(string);

// función: es de tipo distinto a void y debe retornar un valor del tipo definido
float calcularSuma(float, float);

int main() {

	procedimiento("Juan Pérez");

	cout << "19 + 252 = " << calcularSuma(19, 252) << endl;

	return 0;
}

// implementaciones de funciones declaradas anteriormente

void procedimiento(string nombre) {
	cout << "Hola, " << nombre << endl;
}

float calcularSuma(float a, float b) {
	return a + b;
}
