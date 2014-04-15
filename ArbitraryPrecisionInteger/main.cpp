#include "arbitrary_precision_integer.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;

int main() {
	srand(213123213);

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