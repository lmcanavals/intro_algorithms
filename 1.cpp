#include "upc.h"

using namespace std;

const int BOXW = 4;
const int BOXH = 5;


void cuadradito(int n, int x, int y) {
    gotoxy(x, y);
    for (int i = 0; i < BOXW; ++i) {
        cout << n;
    }
    for (int i = 0; i < BOXH - 2; ++i) {
        gotoxy(x, y + i + 1); cout << n << "  " << n;
    }
    gotoxy(x, y + BOXH - 1);
    for (int i = 0; i < BOXW; ++i) {
        cout << n;
    }
}

void line(int n, int num, int x, int y) {
    for (int i = 0; i < n; ++i) {
        cuadradito(num, x + i * BOXW, y);
    }
}

int main() {
    int n;

    n = readIntRange("Ingrese N [1..9]: ", 1, 9);

    clear();

    int x = 0;
    int y = 0;
    for (int i = n; i > 0; --i) {
        line(i, i, x, y);
        x += BOXW/2;
        y += BOXH;
    }
    cout << endl;

    return 0;
}
