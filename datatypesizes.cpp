#include <iostream>

using namespace std;

int main() {
    char var1;
    unsigned char var2;
    signed char var3;
    int                        var4;
    unsigned int            var5;
    signed int                var6;
    short int                var7;
    unsigned short int        var8;
    signed short int        var9;
    long int                var10;
    signed long int            var11;
    unsigned long int        var12;
    long long int            var13;
    unsigned long long int    var14;
    float                    var15;
    double                    var16;
    long double                var17;
    wchar_t                    var18;

    char* ptr1;
    unsigned char* ptr2;
    signed char* ptr3;
    int* ptr4;
    unsigned int* ptr5;
    signed int* ptr6;
    short int* ptr7;
    unsigned short int* ptr8;
    signed short int* ptr9;
    long int* ptr10;
    signed long int* ptr11;
    unsigned long int* ptr12;
    long long int* ptr13;
    unsigned long long int* ptr14;
    float* ptr15;
    double* ptr16;
    long double* ptr17;
    wchar_t* ptr18;

    cout << "Size of char                   : " << sizeof(var1) << endl;
    cout << "Size of unsigned char          : " << sizeof(var2) << endl;
    cout << "Size of signed char            : " << sizeof(var3) << endl;
    cout << "Size of int                    : " << sizeof(var4) << endl;
    cout << "Size of unsigned int           : " << sizeof(var5) << endl;
    cout << "Size of signed int             : " << sizeof(var6) << endl;
    cout << "Size of short int              : " << sizeof(var7) << endl;
    cout << "Size of unsigned short int     : " << sizeof(var8) << endl;
    cout << "Size of signed short int       : " << sizeof(var9) << endl;
    cout << "Size of long int               : " << sizeof(var10) << endl;
    cout << "Size of signed long int        : " << sizeof(var11) << endl;
    cout << "Size of unsigned long int      : " << sizeof(var12) << endl;
    cout << "Size of long long int          : " << sizeof(var13) << endl;
    cout << "Size of unsigned long long int : " << sizeof(var14) << endl;
    cout << "Size of float                  : " << sizeof(var15) << endl;
    cout << "Size of double                 : " << sizeof(var16) << endl;
    cout << "Size of long double            : " << sizeof(var17) << endl;
    cout << "Size of wchar_t                : " << sizeof(var18) << endl;

    cout << "Size of pointer to char                   : " << sizeof(ptr1) << endl;
    cout << "Size of pointer to unsigned char          : " << sizeof(ptr2) << endl;
    cout << "Size of pointer to signed char            : " << sizeof(ptr3) << endl;
    cout << "Size of pointer to int                    : " << sizeof(ptr4) << endl;
    cout << "Size of pointer to unsigned int           : " << sizeof(ptr5) << endl;
    cout << "Size of pointer to signed int             : " << sizeof(ptr6) << endl;
    cout << "Size of pointer to short int              : " << sizeof(ptr7) << endl;
    cout << "Size of pointer to unsigned short int     : " << sizeof(ptr8) << endl;
    cout << "Size of pointer to signed short int       : " << sizeof(ptr9) << endl;
    cout << "Size of pointer to long int               : " << sizeof(ptr10) << endl;
    cout << "Size of pointer to signed long int        : " << sizeof(ptr11) << endl;
    cout << "Size of pointer to unsigned long int      : " << sizeof(ptr12) << endl;
    cout << "Size of pointer to long long int          : " << sizeof(ptr13) << endl;
    cout << "Size of pointer to unsigned long long int : " << sizeof(ptr14) << endl;
    cout << "Size of pointer to float                  : " << sizeof(ptr15) << endl;
    cout << "Size of pointer to double                 : " << sizeof(ptr16) << endl;
    cout << "Size of pointer to long double            : " << sizeof(ptr17) << endl;
    cout << "Size of pointer to wchar_t                : " << sizeof(ptr18) << endl;

    double var = 1e-100;
    double* ptrvar1 = &var;
    float* ptrvar2 = (float*)&var;
    int* ptrvar3 = (int*)&var;
    char* ptrvar4 = (char*)&var;

    cout << var << endl;
    cout << *ptrvar1 << endl;
    cout << *ptrvar2 << endl;
    cout << *ptrvar3 << endl;
    cout << *ptrvar4 << endl;

    /*double* ptr = (double*)248756234786234;

    *ptr = 1.1e-150;

    cout << *ptr << endl;*/

    return 0;
}