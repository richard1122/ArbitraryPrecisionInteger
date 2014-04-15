#include "arbitrary_precision_integer.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;

int main() {
	srand(213123213);

	/*
	int a = 24024, b = 240;
	ArbitraryPrecisionInteger BigA(a), BigB(b);
	ArbitraryPrecisionInteger BigAns = BigA / BigB;
	int ans = a / b;
	assert(BigAns == ArbitraryPrecisionInteger(ans));
	cout << "Assert " << a << '-' << b << " success" << endl;
	*/

	while (true) {
		int a, b;
		int ans;
		a = rand();
		b = rand();
		
		ArbitraryPrecisionInteger BigA(a), BigB(b);

		ans = a + b;
		ArbitraryPrecisionInteger BigAns = BigA + BigB;
		assert(BigAns == ArbitraryPrecisionInteger(ans));
		cout << "Assert " << a << '+' << b << " success" << endl;

		ans = a - b;
		BigAns = BigA - BigB;
		assert(BigAns == ArbitraryPrecisionInteger(ans));
		cout << "Assert " << a << '-' << b << " success" << endl;

		ans = a * b;
		BigAns = BigA * BigB;
		assert(BigAns == ArbitraryPrecisionInteger(ans));
		cout << "Assert " << a << '*' << b << " success" << endl;

		if (b == 0) continue;
		ans = a / b;
		BigAns = BigA / BigB;
		assert(BigAns == ArbitraryPrecisionInteger(ans));
		cout << "Assert " << a << '/' << b << " success" << endl;

		ans = a % b;
		BigAns = BigA % BigB;
		assert(BigAns == ArbitraryPrecisionInteger(ans));
		cout << "Assert " << a << '%' << b << " success" << endl;

	}
	system("pause");
	return 0;
}