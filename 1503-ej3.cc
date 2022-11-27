#include "upc.h"
#include <chrono>

#define MAX 30

using namespace std;

struct Call {
	int code;
	int landLineMins;
	int cellphoneMins;
	int numsms;
};

Call* makeCalls() {
	Call* calls = new Call[MAX];
	for (int i = 0; i < MAX; ++i) {
		calls[i].code = 201 + i;
		calls[i].landLineMins = randint(0, 100);
		calls[i].cellphoneMins = randint(0, 100);
		calls[i].numsms = randint(0, 100);
	}
	return calls;
}

void topCellphoneCallers(Call* calls) {
	int max = 0;
	for (int i = 0; i < MAX; ++i) {
		if (calls[i].cellphoneMins > max) max = calls[i].cellphoneMins;
	}
	cout << "Top cellphone callers: \n";
	for (int i = 0; i < MAX; ++i) {
		if (calls[i].cellphoneMins == max) {
			cout << calls[i].code << " ";
		}
	}
	cout << endl;
}

void calc(Call* calls) {
	for (int i = 0; i < MAX; ++i) {
		float pay = 0.0f;
		pay += calls[i].landLineMins <= 20? 0
			: (calls[i].landLineMins - 20) * .35f;
		pay += calls[i].cellphoneMins <= 40? 0
			: (calls[i].cellphoneMins - 40) * .45f;
		pay += calls[i].numsms <= 20? 0
			: (calls[i].numsms - 20) * .2f;
		cout << "Salesperson " << calls[i].code << " payment S/ " << pay << endl;
	}
}

void avg(Call* calls) {
	float avgLL = 0;
	float avgCP = 0;
	float avgSMS = 0;
	for (int i = 0; i < MAX; ++i) {
		avgLL += calls[i].landLineMins;
		avgCP += calls[i].cellphoneMins;
		avgSMS += calls[i].numsms;
	}
	cout << "promedio de llamadas a fijo: " << avgLL / MAX << endl;
	cout << "promedio de llamadas a celular: " << avgCP / MAX << endl;
	cout << "promedio de sms: " << avgSMS / MAX << endl;
}

int main() {
	srand(chrono::system_clock::now().time_since_epoch().count());
	Call* calls = makeCalls();

	topCellphoneCallers(calls);
	calc(calls);
	avg(calls);

	delete[] calls;

	return 0;
}
