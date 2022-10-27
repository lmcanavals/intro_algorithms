#include <iomanip>
#include "upc.h"

using namespace std;

int main() {
	for (int i = 0; i < 16; ++i) {
		clearColor();
		background(i);
		cout << " H ";
		foreground(i);
		cout << setw(2) << i;
	}
	clearColor();
	cout << endl;
	for (int i = 0; i < 16; ++i) {
		clearColor();
		background(i);
		cout << i; clearColor(); cout << endl;
	}
	for (int i = 0; i < 16; ++i) {
		clearColor();
		foreground(i);
		cout << i; clearColor(); cout << endl;
	}

	return 0;
}
