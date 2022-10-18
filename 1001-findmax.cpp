#include <stdlib.h>
#include <iomanip>

#include "upc.h"

using namespace std;

int findMax(int* arr, int n) {
	int m = arr[0];
	for (int i = 1; i < n; ++i) {
		if (arr[i] > m) {
			m = arr[i];
		}
	}
	return m;
}

int main() {
	int n;

	n = readIntRange("Ingrese n[2..20]: ", 2, 20);

	int* arr = new int[n];

	srand(time(nullptr));
	for (int i = 0; i < n; ++i) {
		arr[i] = rand() % 100;
		cout << "Arreglo[" << setw(2) << i << "]: "
			<< setw(3) << arr[i] << endl;
	}

	cout << "El mayor es: " << findMax(arr, n) << endl;

	delete[] arr;

	return 0;
}

