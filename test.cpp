#include <iostream>
#include <ostream>
#include "upc.h"

using namespace std;

int main() {
  cout << "Hola, Mundo!\n";
	for (;;) {
		if (_kbhit()) {
			int x = _getch();
			cout << endl
				<< x << endl
				<< (char) x << endl 
				<< (char) (x&0x000000ff) << endl
				<< (char) ((x&0x0000ff00) >> 8) << endl
				<< (char) ((x&0x00ff0000) >> 8) << endl
				<< (char) ((x&0xff000000) >> 8) << endl
				<< "----------------\n";
		}
	}

  return 0;
}
