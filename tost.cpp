#include <iostream>
using namespace std;
#include <ctime>
#include<stdlib.h>

int main()
{
	int n = 0, i, j, k;
	char t;
	do 
	{
	cout << "Ingrese un numero entero menor que 10 pero mayor o igual a 3: ";
	cin >> n;
	} 
	while ((n >= 10) || (n < 3));

	for (k = 1;k <= n;k++) {
		for (i = 1;i <= 8;i++) {
			for (j = 1;j <= 8;j++) {
				if (i == 1 || i == 8 || i == j || (i + j == 9)) {
					t = 'A' + rand() % 26;
					cout << t;
				}
				else {
					cout << " ";
				}

			}
			cout << "\n";
		}
		cout << "\n\n";
	}

	return 0;
}
