#include "arbitrary_precision_integer.h"
#include <iostream>
using namespace std;

int main() {
	AubitraryPrecisionInteger a(12345), b(-12344);
	AubitraryPrecisionInteger result = a + b;
	result.raw_output(cout);
	cout << (a < b) << endl;
	system("pause");
	return 0;
}