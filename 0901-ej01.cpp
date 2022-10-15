#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

void random4(size_t* a, size_t* b, size_t* c, size_t* d) {
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

size_t max(size_t* a, size_t* b, size_t* c, size_t* d) {
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

size_t min(size_t* a, size_t* b, size_t* c, size_t* d) {
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

int main() {
    srand(time(nullptr));

    char* op = new char;
    size_t* a = new size_t;
    size_t* b = new size_t;
    size_t* c = new size_t;
    size_t* d = new size_t;

    do {
        random4(a, b, c, d);

        cout << *a << " " << *b << " " << *c << " " << *d << endl;
        cout << max(a, b, c, d) << endl;

        *op = _getch();
    } while (*op != 'x');

    delete op;
    delete a;
    delete b;
    delete c;
    delete d;


    return 0;
}
