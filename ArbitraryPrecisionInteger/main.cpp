#include "arbitrary_precision_integer.h"
#include <iostream>
using namespace std;

int main() {
	ArbitraryPrecisionInteger a(1);
	for (int i = 2; i != 100; ++i) {
		a = a * i;
	}
	a.raw_output(cout);
	system("pause");
	return 0;
}