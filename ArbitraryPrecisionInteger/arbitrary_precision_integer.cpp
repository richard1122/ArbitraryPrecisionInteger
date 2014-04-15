#include "arbitrary_precision_integer.h"
#include <iostream>
using namespace std;

ArbitraryPrecisionInteger::ArbitraryPrecisionInteger() :length(0), negative(false) {};

ArbitraryPrecisionInteger::ArbitraryPrecisionInteger(int num) {
	ArbitraryPrecisionInteger();
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
	}

	ArbitraryPrecisionInteger temp(length, digit, false);
	temp.resetZero();
	return temp;
}

void ArbitraryPrecisionInteger::raw_output(ostream &os) const {
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

ArbitraryPrecisionInteger operator- (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	return NULL;
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

ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &a, const ArbitraryPrecisionInteger &b) {
	return NULL;
}

void ArbitraryPrecisionInteger::operator=(const ArbitraryPrecisionInteger &num) {
	this->negative = num.isNegative();
	this->digit = num.digit;
	this->length = num.length;
}

ArbitraryPrecisionInteger operator<< (const ArbitraryPrecisionInteger &a, int times) {
	vector<int> digit = a.digit;
	vector<int> zeros(times, 0);
	digit.insert(digit.begin(), zeros.begin(), zeros.end());
	return ArbitraryPrecisionInteger(a.length + times, digit, a.isNegative());
}

