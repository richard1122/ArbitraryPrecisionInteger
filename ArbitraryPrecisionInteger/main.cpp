#include "arbitrary_precision_integer.h"
#include <iostream>
using namespace std;

int main() {
	ArbitraryPrecisionInteger a(100), b(1);
	ArbitraryPrecisionInteger ans = a % b;
	ans.raw_output(cout);
	system("pause");
	return 0;
}