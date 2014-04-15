#include "arbitrary_precision_integer.h"
#include <iostream>
using namespace std;

int main() {
	ArbitraryPrecisionInteger a(12345), b(0);
	ArbitraryPrecisionInteger result = a * b;
	result.raw_output(cout);
	system("pause");
	return 0;
}