#pragma once

#include <iostream>
#include <string>

using namespace std;

bool isInt(string str) {
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
	}
	return str.size() > 0;
}

int readInt(string msg) {
	string str;
	do {
		cout << msg; getline(cin, str);
		if (!isInt(str)) {
			cout << "<" << str << "> no es un número entero.\n";
		}
	} while (!isInt(str));
	return stoi(str);
}

int readIntRange(string msg, int min, int max) {
	int num;
	do {
		num = readInt(msg);
		if (num < min || num > max) {
			cout << "<" << num << "> no está en el rango [" << min << ".." << max << "]\n";
		}
	} while (num < min || num > max);
	return num;
}
