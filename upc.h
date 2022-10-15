#include <stdlib.h>
#include <time.h>
#include <iomanip>

#include "upc.h"

using namespace std;

void random4(unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d) {
    *a = (rand() % 40) + 1;
    do {
        *b = (rand() % 40) + 1;
    } while (*b == *a);
    do {
        *c = (rand() % 40) + 1;
    } while (*c == *a || *c == *b);
    do {
        *d = (rand() % 40) + 1;
    } while (*d == *a || *d == *b || *d == *c);
}

unsigned int max4(unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d) {
    if (*a > *b && *a > *c && *a > *d) {
        return *a;
    }
    if (*b > *c && *b > *d) {
        return *b;
    }
    if (*c > *d) {
        return *c;
    }
    return *d;
}

unsigned int min4(unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d) {
    if (*a < *b && *a < *c && *a < *d) {
        return *a;
    }
    if (*b < *c && *b < *d) {
        return *b;
    }
    if (*c < *d) {
        return *c;
    }
    return *d;
}

unsigned int maxOf3(unsigned int* a, unsigned int* b, unsigned int* c) {
    if (*a > *b && *a > *c) {
        return *a;
    }
    if (*b > *c) {
        return *b;
    }
    return *c;
}

unsigned int secondMax(unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d) {
    unsigned int x = max4(a, b, c, d);
    if (*a == x) {
        return maxOf3(b, c, d);
    }
    if (*b == x) {
        return maxOf3(a, c, d);
    }
    if (*c == x) {
        return maxOf3(a, b, d);
    }
    return maxOf3(a, b, c);
}

void stars(int x, int y, int n) {
    for (int i = 0; i < n; ++i) {
        gotoxy(x - i, y);
        cout << "*";
    }
}

void graph(unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d) {
    stars(79, 2, *a); gotoxy(79 - *a - 1, 2); cout << setw(2) << *a;
    stars(79, 3, *b); gotoxy(79 - *b - 1, 3); cout << setw(2) << *b;
    stars(79, 4, *c); gotoxy(79 - *c - 1, 4); cout << setw(2) << *c;
    stars(79, 5, *d); gotoxy(79 - *d - 1, 5); cout << setw(2) << *d;
}

int main() {
    srand(time(nullptr));

    char* op = new char;
    unsigned int* a = new unsigned int;
    unsigned int* b = new unsigned int;
    unsigned int* c = new unsigned int;
    unsigned int* d = new unsigned int;

    do {
        random4(a, b, c, d);

        clear();
        graph(a, b, c, d);
        cout << endl;
        cout << *a << " " << *b << " " << *c << " " << *d << endl;
        cout << max4(a, b, c, d) << endl;
        cout << secondMax(a, b, c, d) << endl;

        *op = _getch();
    } while (*op != 'x');

    delete op;
    delete a;
    delete b;
    delete c;
    delete d;


    return 0;
}
