#include "upc.h"

using namespace std;

bool isEven(int n) {
    return n % 2 == 0;
}

int main() {
    int n;
    int inc;
    int x, y;

    n = readIntRange("N [1..9]: ", 1, 9);
    clear();

    for (int k = n; k > 0; --k) {
        inc = isEven(k) ? 1 : -1;
        x = k;
        y = isEven(k)? k : n;
    
        for (int i = 0; i < n - k + 1; ++i) {
            gotoxy(x, y);
            cout << k << endl;
            y += inc;
            sleep4(500);
        }
    }

    gotoxy(0, n + 1);

    return 0;
}
