#include <iomanip>

#include "upc.h"

using namespace std;

void repeatstr(int n, string str) {
    for (int i = 0; i < n; ++i) {
        cout << setw(2) << str;
    }
}

void repeatstr2(int n, int num) {
    for (int i = 0; i < n; ++i) {
        cout << setw(2) << num;
    }
}

void starline(int n, int stars, int spaces) {
    repeatstr(spaces, " ");
    cout << setw(2) << n;
    repeatstr(stars, "*");
    cout << setw(2) << n;
    cout << endl;
}

int main() {
    int n;
    int t, stars, spaces;

    n = readIntRange("Ingrese N [1..99]: ", 1, 99);

    repeatstr(n, "1"); cout << endl;
    t = n / 2;
    stars = n - 4;
    for (int i = 2; i <= t; ++i) {
        spaces = i - 1;
        starline(i, stars, spaces);
        stars -= 2;
    }
    if (n % 2 == 0) {
        starline(t + 1, 0, spaces);
        stars += 2;
    } else {
        spaces += 1;
        repeatstr(spaces, " "); cout << setw(2) << t + 1 << endl;
    }

    for (int i = t + 2; i < n; ++i) {
        --spaces;
        stars += 2;
        starline(i, stars, spaces);
    }
    repeatstr2(n, n); cout << endl;

    return 0;
}