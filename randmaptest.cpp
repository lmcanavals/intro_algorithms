#include <iostream>

using namespace std;

#include "randmap.h"

int main() {
    srand(time(nullptr));
    int rows = 15;
    int cols = 37;
    int** lab = randLab(rows, cols);
    char glyphs[] = { ' ', '|', '-', '+' };

    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << glyphs[lab[i][j]];
        }
        cout << endl;
    }
    
    for (int i = 0; i < rows; ++i) {
        delete[] lab[i];
    }
    delete[] lab;

    return 0;
}
