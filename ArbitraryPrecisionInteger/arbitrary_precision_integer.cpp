#include "arbitrary_precision_integer.h"
#include <iostream>
using namespace std;

ArbitraryPrecisionInteger::ArbitraryPrecisionInteger() :length(0), negative(false) {};

ArbitraryPrecisionInteger::ArbitraryPrecisionInteger(int num) : ArbitraryPrecisionInteger() {
	if (num < 0) negative = true, num = -num;
	while (num) {
		digit.push_back(num % 10);
		++length;
		num /= 10;
	}
	resetZero();
}

ArbitraryPrecisionInteger::ArbitraryPrecisionInteger(const int &len, const vector<int> &vec, bool negative) {
	ArbitraryPrecisionInteger();
	this->length = len;
	this->digit = vec;
	this->negative = negative;
}

bool ArbitraryPrecisionInteger::isNegative() const {
	return this->negative;
}

void ArbitraryPrecisionInteger::resetZero() {
	while (length > 0 && digit.back() == 0) {
		--length;
		digit.pop_back();
	}
}

ArbitraryPrecisionInteger ArbitraryPrecisionInteger::add(const ArbitraryPrecisionInteger &num) const {
	vector <int> digit;
	int length;

	int carry = 0;
	int len = max(this->length, num.length);
	for (length = 0; length != len; ++length) {
		if (length < this->length)
			carry += this->digit[length];
		if (length < num.length)
			carry += num.digit[length];

		digit.push_back(carry % 10);
		carry /= 10;
	}

	if (carry != 0) {
		digit.push_back(carry);
		++length;
	}
	return ArbitraryPrecisionInteger(length, digit, false);
}

ArbitraryPrecisionInteger ArbitraryPrecisionInteger::sub(const ArbitraryPrecisionInteger &num) const {
	vector<int> digit(this->length);
	int length;
	int carry = 0;

	for (length = 0; length != num.length; ++length) {
		digit[length] = this->digit[length] - num.digit[length] - carry;
		carry = 0;
		if (digit[length] < 0) digit[length] += 10, carry = 1;
	}

	while (length != this->length) {
		digit[length] = this->digit[length] - carry;
		carry = 0;
		if (digit[length] < 0) digit[length] += 10, carry = 1;
		++length;
	}

	ArbitraryPrecisionInteger temp(length, digit, false);
	temp.resetZero();
	return temp;
}

ArbitraryPrecisionInteger ArbitraryPrecisionInteger::singleMul(int n) const {
	vector<int> digit;
	int carry = 0;

	for (auto iter : this->digit) {
		int sum = carry + iter * n;
		digit.push_back(sum % 10);
		carry = sum / 10;
	}

	while (carry != 0) {
		digit.push_back(carry % 10);
		carry /= 10;
	}
	return ArbitraryPrecisionInteger(digit.size(), digit, false);
}

void ArbitraryPrecisionInteger::raw_output(ostream &os) const {
	if (digit.size() == 0) {
		cout << '0' << endl;
		return;
	}

	if (negative) cout << '-';
	for (auto ai = digit.rbegin(); ai != digit.rbegin() + length; ++ai)
		os << *ai;
	os << endl;
}

ArbitraryPrecisionInteger operator+ (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	if (a.isNegative() && b.isNegative()) {
		return (-a).add(-b) * false;
	}

	if (a.isNegative() && !b.isNegative()) {
		if (-a < b) return b.sub(-a) * false;
		else return (-a).sub(b) * true;
	}

	if (!a.isNegative() && b.isNegative()) {
		if (a < -b) return (-b).sub(a) * true;
		else return a.sub(-b) * false;
	}
	return a.add(b);
}

ArbitraryPrecisionInteger operator+ (const ArbitraryPrecisionInteger &a, int n) {
	ArbitraryPrecisionInteger temp(n);
	return a + temp;
}

ArbitraryPrecisionInteger operator- (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	return a + -b;
}

ArbitraryPrecisionInteger operator- (const ArbitraryPrecisionInteger &num) {
	return ArbitraryPrecisionInteger(num.length, num.digit, !num.negative);
}

bool operator< (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	if (a.length < b.length) return true;
	if (a.length > b.length) return false;

	auto aIter = a.digit.rbegin();
	auto bIter = b.digit.rbegin();

	while (aIter != a.digit.rend() && bIter != b.digit.rend()) {
		if (*aIter == *bIter) {
			++aIter;
			++bIter;
			continue;
		}
		return *aIter < *bIter;
	}
	return false;
}

bool operator>(const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	return b < a;
}

ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &a, bool negative) {
	return ArbitraryPrecisionInteger(a.length, a.digit, a.isNegative() ^ negative);
}

ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &a, int n) {
	bool negative = a.isNegative() ^ (n < 0);

	return a.singleMul(n) * negative;
}

ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	ArbitraryPrecisionInteger answer;
	bool negative = a.isNegative() ^ b.isNegative();

	for (int i = 0; i != b.length; ++i) {
		answer = answer + ((a * b.digit[i]) << i);
	}
	
	answer.negative = negative;
	answer.resetZero();
	return answer;
}

ArbitraryPrecisionInteger& ArbitraryPrecisionInteger::operator=(const ArbitraryPrecisionInteger &num) {
	this->negative = num.isNegative();
	this->digit = num.digit;
	this->length = num.length;
	return *this;
}

ArbitraryPrecisionInteger operator<< (const ArbitraryPrecisionInteger &a, int times) {
	vector<int> digit = a.digit;
	vector<int> zeros(times, 0);
	digit.insert(digit.begin(), zeros.begin(), zeros.end());
	ArbitraryPrecisionInteger temp(a.length + times, digit, a.isNegative());
	temp.resetZero();
	return temp;
}

ArbitraryPrecisionInteger operator/ (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	ArbitraryPrecisionInteger tempA = a, tempB = b;

	bool negative = tempA.isNegative() ^ tempB.isNegative();
	if (a.isNegative()) tempA = -tempA;
	if (b.isNegative()) tempB = -tempB;

	ArbitraryPrecisionInteger temp, ans;
	auto iter = tempA.digit.rbegin();
	while (true) {
		if (iter == tempA.digit.rend()) break;
		temp = (temp << 1) + *iter;
		++iter;
		if (temp < tempB) {
			ans = ans << 1;
			continue;
		}
		for (int i = 9; i >= 1; --i) {
			if (temp >= b * i) {
				// 找到了一个可用的解
				ans = (ans << 1) + i;
				temp = temp - b * i;
				break;
			}
		}
	}
	ans.resetZero(); 
	ans.negative = negative;
	return ans;
}

ArbitraryPrecisionInteger operator% (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	return a - a / b * b;
}

bool operator== (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	return !(a < b || a > b);
}

bool operator>=(const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	return !(a < b);
}