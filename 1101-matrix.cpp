#include <iomanip>

#include "upc.h"

using namespace std;

float** randMatrix(int rows, int cols) {
	float** mat = new float*[rows];
	for (int i = 0; i < rows; ++i) {
		mat[i] = new float[cols];

		for (int j = 0; j < cols; ++j) {
			mat[i][j] = (float)randint(1, 101);
		}
	}
	return mat;
}

void deleteMat(float** mat, int rows) {
	for (int i = 0; i < rows; ++i) {
		delete[] mat[i];
	}
	delete[] mat;
}

float** add(float** a, float** b, int rows, int cols) {
	float** c = new float*[rows];
	for (int i = 0; i < rows; ++i) {
		c[i] = new float[cols];

		for (int j = 0; j < cols; ++j) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

void showMatrix(float** a, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << setw(4) << a[i][j];
		}
		cout << endl;
	}
}

int main() {
	int rows = 5;
	int cols = 10;
	float** a = randMatrix(rows, cols);
	float** b = randMatrix(rows, cols);
	float** c = add(a, b, rows, cols);

	showMatrix(a, rows, cols);
	cout << endl;
	showMatrix(b, rows, cols);
	cout << endl;
	showMatrix(c, rows, cols);

	deleteMat(a, rows);
	deleteMat(b, rows);
	deleteMat(c, rows);

	return 0;
}

// pcsilcan@upc.edu.pe