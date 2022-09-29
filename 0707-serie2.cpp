#include "upc.h"

using namespace std;

long long factorial(int n) {
    long long f = 1;

    for (int i = 2; i <= n; ++i) {
        f *= i;
    }

    return f;
}

int main() {
    int* inc = new int;
    int* a = new int;
    long long* t1 = new long long;
    float* t2 = new float;
    float* ti = new float;
    float* S = new float;
    int* n = new int; // cantidad de terminos;
    int* signo = new int;

    *n = readIntRange("Ingrese cantidad de terminos [1..20]: ", 1, 20);
    *a = readIntRange("Ingrese A [1..4]: ", 1, 4);

    *inc = 4;
    *t2 = 2;
    *signo = 1;
    *S = 0;

    cout << "Los terminos son:" << endl;
    for (int i = 1; i <= *n; ++i) {
        *t1 = *a * factorial(*a + i);
        *ti = *signo * *t1 / *t2;
        *S += *ti;
        *t2 += *inc;
        *inc += 2;
        *signo *= -1;

        cout << *ti << " ";
    }
    cout << endl << "Suma de terminos: " << *S << endl;

    delete inc;
    delete a;
    delete t1;
    delete t2;
    delete ti;
    delete S;
    delete n;
    delete signo;

    return 0;
}
