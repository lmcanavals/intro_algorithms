#include "upc.h"

#include <ctime>
#include <string>

using namespace std;

int** makeMat(int size) {
	int** m = new int*[size];
	for (int i = 0; i < size; ++i) {
		m[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			m[i][j] = BRIGHT_BLACK;
		}
	}
	return m;
}

char** randMat(int size) {
	char** m = new char*[size];
	for (int i = 0; i < size; ++i) {
		m[i] = new char[size];
		for (int j = 0; j < size; ++j) {
			m[i][j] = randint('0', '9' + 1);
		}
	}
	return m;
}

void printMat(char** mat, int** col, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			color(col[i][j]);
			cout << mat[i][j] << " "; 
			clearColor();
		}
		cout << endl;
	}
}

int patternIn(string s, char* line, int size, int start) {
	for (int i = start; i < size - s.size() + 1; ++i) {
		bool found = true;
		for (int j = 0; j < s.size(); ++j) {
			if (s[j] != line[i + j]) {
				found = false;
				break;
			}
		}
		if (found) return i;
	}
	return -1;
}

int main() {
	srand(time(nullptr));
	int N = readIntRange("Ingrese el tamaño de la matriz: ", 1, 30);
	char** m = randMat(N);
	int** color = makeMat(N);
	int pattern = readIntRange("Ingrese patrón numérico: ", 0, 1000);
	string s = to_string(pattern);

	int cont = 0;
	for (int i = 0; i < N; ++i) {
		int start = 0;
		do {
			start = patternIn(s, m[i], N, start);
			if (start >= 0) {
				for (int j = 0; j < s.size(); ++j) {
					color[i][start + j] = BRIGHT_RED;
				}
				++cont;
				++start;
			}
		} while (start >= 0);
	}
	cout << "El número de veces que se repite el patrón es: " << cont << endl;
	printMat(m, color, N);

	for (int i = 0; i < N; ++i) {
		delete[] m[i];
		delete[] color[i];
	}
	delete[] m;
	delete[] color;

	return 0;
}
