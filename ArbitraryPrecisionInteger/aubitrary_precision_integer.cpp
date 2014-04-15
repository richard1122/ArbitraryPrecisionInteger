#include "arbitrary_precision_integer.h"
#include <iostream>
using namespace std;

AubitraryPrecisionInteger::AubitraryPrecisionInteger() :length(0), negative(false) {};

AubitraryPrecisionInteger::AubitraryPrecisionInteger(int num) {
	AubitraryPrecisionInteger();
	if (num < 0) negative = true, num = -num;
	while (num) {
		digit.push_back(num % 10);
		++length;
		num /= 10;
	}
	resetZero();
}

AubitraryPrecisionInteger::AubitraryPrecisionInteger(const int &len, const vector<int> &vec, bool negative) {
	AubitraryPrecisionInteger();
	this->length = len;
	this->digit = vec;
	this->negative = negative;
}

bool AubitraryPrecisionInteger::isNegative() const {
	return this->negative;
}

void AubitraryPrecisionInteger::resetZero() {
	while (length > 0 && digit.back() == 0) {
		--length;
		digit.pop_back();
	}
}

AubitraryPrecisionInteger AubitraryPrecisionInteger::add(const AubitraryPrecisionInteger &num) const {
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
	return AubitraryPrecisionInteger(length, digit, false);
}

AubitraryPrecisionInteger AubitraryPrecisionInteger::sub(const AubitraryPrecisionInteger &num) const {
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

	AubitraryPrecisionInteger temp(length, digit, false);
	temp.resetZero();
	return temp;
}

void AubitraryPrecisionInteger::raw_output(ostream &os) const {
	if (negative) cout << '-';
	for (auto ai = digit.rbegin(); ai != digit.rbegin() + length; ++ai)
		os << *ai;
	os << endl;
}

AubitraryPrecisionInteger operator+ (const AubitraryPrecisionInteger &a, const AubitraryPrecisionInteger &b) {
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

AubitraryPrecisionInteger operator- (const AubitraryPrecisionInteger &a, const AubitraryPrecisionInteger &b) {
	return NULL;
}

AubitraryPrecisionInteger operator- (const AubitraryPrecisionInteger &num) {
	return AubitraryPrecisionInteger(num.length, num.digit, !num.negative);
}

bool operator< (const AubitraryPrecisionInteger &a, const AubitraryPrecisionInteger &b) {
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

bool operator>(const AubitraryPrecisionInteger &a, const AubitraryPrecisionInteger &b) {
	return b < a;
}

AubitraryPrecisionInteger operator* (const AubitraryPrecisionInteger &a, bool negative) {
	return AubitraryPrecisionInteger(a.length, a.digit, a.isNegative() ^ negative);
}

void AubitraryPrecisionInteger::operator=(const AubitraryPrecisionInteger &num) {
	this->negative = num.isNegative();
	this->digit = num.digit;
	this->length = num.length;
}

AubitraryPrecisionInteger operator<< (const AubitraryPrecisionInteger &a, int times) {
	vector<int> digit = a.digit;
	vector<int> zeros(times, 0);
	digit.insert(digit.begin(), zeros.begin(), zeros.end());
	return AubitraryPrecisionInteger(a.length + times, digit, a.isNegative());
}