#include <iostream>

using namespace std;

void proc1(float& param1, float* param2, float param3) {
	cout << "Dirección de varible param1: " << &param1 << endl;
	cout << "Dirección de varible apuntada por param2: " << param2 << endl;
	cout << "Dirección de varible param3: " << &param3 << endl;
}


int main() {
	float normal;
	float* ptr = new float;

	cout << "dirección de variable normal: " << &normal << endl;
	cout << "Dirección apuntada por ptr: " << ptr << endl;

	proc1(normal, &normal, normal);
	proc1(*ptr, ptr, *ptr);

	delete ptr;
	return 0;
}
