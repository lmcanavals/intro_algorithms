#include <iostream>
#include <string>

using namespace std;

bool isInt(string str) {
	int i = 0;
	while (i < str.size()) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
		i++;
	}
	return true;
}

int main() {
	string num;
	do {
		cout << "Ingrese un número: "; cin >> num;
		if (!isInt(num)) {
			cerr << "<" << num << "> no es un número.\n";
			cerr << "Intente nuevamente...\n";
		}
	} while (!isInt(num));

	cout << "Felicitaciones, <" << num << "> es un número entero.\n";

	return 0;
}
