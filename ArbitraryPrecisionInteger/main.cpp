#include "arbitrary_precision_integer.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
using namespace std;

const int COUNT = 6;
const int WIDTH = 128;

// 生成一个超大的随机数，传入二进制位宽
ArbitraryPrecisionInteger generateArbitraryPrecisionRandomInteger(int);
// a^b % p
ArbitraryPrecisionInteger modular(
	ArbitraryPrecisionInteger,
	ArbitraryPrecisionInteger,
	ArbitraryPrecisionInteger
	);
// 整数测试（简单的进行大整数运算测试
void integerTest();
// Miller-Rabin primality test, iteration signifies the accuracy of the test
bool Miller(ArbitraryPrecisionInteger, int);
// 生成一个大随机素数
ArbitraryPrecisionInteger generateArbitraryPrimeInteger(int);

int main() {
	srand((unsigned int) time(NULL));

	ArbitraryPrecisionInteger g = generateArbitraryPrimeInteger(WIDTH), p = generateArbitraryPrimeInteger(WIDTH);
	cout << "Alice choose prime: \t";
	g.raw_output(cout);
	cout << "Bob choose prime: \t";
	p.raw_output(cout);
	cout << endl;

	const int a = rand() % 32 + 1, b = rand() % 32 + 1;
	cout << "Alice choose secret integer: \t" << a << endl;
	cout << "Bob choose secret integer: \t" << b << endl;
	cout << endl;

	ArbitraryPrecisionInteger A = g.pow(a) % p;
	ArbitraryPrecisionInteger B = g.pow(b) % p;
	cout << "Alice's A is: \t";
	A.raw_output(cout);
	cout << "Bob's B is: \t";
	B.raw_output(cout);
	cout << endl;

	ArbitraryPrecisionInteger s1 = B.pow(a) % p;
	ArbitraryPrecisionInteger s2 = A.pow(b) % p;
	cout << "Key Alice calc: \t";
	s1.raw_output(cout);
	cout << "Key Bob calc: \t\t";
	s2.raw_output(cout);
	cout << endl;

	cout << "Key exchange complate!\n";

	system("pause");
	return 0;
}

ArbitraryPrecisionInteger generateArbitraryPrimeInteger(int width) {
	ArbitraryPrecisionInteger p = generateArbitraryPrecisionRandomInteger(WIDTH);
	while (!Miller(p, COUNT)) {
		p = generateArbitraryPrecisionRandomInteger(WIDTH);
	}
	return p;
}


bool Miller(ArbitraryPrecisionInteger p, int iteration){
	if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0 || p % 7 == 0){
		return false;
	}
	ArbitraryPrecisionInteger s = p - 1;
	while (s % 2 == 0) {
		s = s / 2;
	}
	for (int i = 0; i < iteration; i++){
		ArbitraryPrecisionInteger a = generateArbitraryPrecisionRandomInteger(WIDTH);
		ArbitraryPrecisionInteger temp = s;
		ArbitraryPrecisionInteger mod = modular(a, temp, p);

		while (temp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mod * mod % p;
			temp = temp * 2;
		}
		if (mod != p - 1 && temp % 2 == 0){
			return false;
		}
	}
	return true;
}



ArbitraryPrecisionInteger modular(
	ArbitraryPrecisionInteger a,
	ArbitraryPrecisionInteger b,
	ArbitraryPrecisionInteger p
	) {
	ArbitraryPrecisionInteger ans = 1;
	a = a % p;
	while (b > 0) {
		if (b % 2 == 1) {
			ans = ans * a % p;
		}
		b = b / 2;
		a = a * a % p;
	}
	return ans;
}


ArbitraryPrecisionInteger generateArbitraryPrecisionRandomInteger(int width) {
	ArbitraryPrecisionInteger random;

	// 分割成16位整数生成，然后再补齐
	int width16 = width / 16;
	width = width % 16;

	while (width16--) {
		random = random * 0xFFFF + (rand() & 0xFFFF);
	}

	while (width--) {
		random = random * 2 + (rand() & 0x1);
	}

	return random;
}

void integerTest() {
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
}