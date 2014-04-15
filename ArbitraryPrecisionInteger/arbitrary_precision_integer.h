#ifndef AUBITRARY_PRECISION_INTEGER
#define AUBITRARY_PRECISION_INTEGER

#include <vector>
#include <algorithm>
using namespace std;

class ArbitraryPrecisionInteger {
private:
	bool negative;
	vector<int> digit;
	int length;

	void resetZero();
	bool isNegative() const;

	// 无符号加法
	ArbitraryPrecisionInteger add(const ArbitraryPrecisionInteger &) const;
	// 无符号减法，保证结果不为负数
	ArbitraryPrecisionInteger sub(const ArbitraryPrecisionInteger &) const;
	// 高精度数乘整数，保证都是正数
	ArbitraryPrecisionInteger singleMul(int) const;

public:
	ArbitraryPrecisionInteger();
	ArbitraryPrecisionInteger(int);
	ArbitraryPrecisionInteger(const int &, const vector<int> &, bool);
	friend ArbitraryPrecisionInteger operator+(const ArbitraryPrecisionInteger&, const ArbitraryPrecisionInteger&);
	friend ArbitraryPrecisionInteger operator+(const ArbitraryPrecisionInteger&, int);
	friend bool operator<(const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	friend bool operator>(const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	friend ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &, bool);
	friend ArbitraryPrecisionInteger operator- (const ArbitraryPrecisionInteger &);
	friend ArbitraryPrecisionInteger operator- (const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	// 左移运算（每次意味着*10)
	friend ArbitraryPrecisionInteger operator<< (const ArbitraryPrecisionInteger &, int);
	// 高精度数乘低精度数
	friend ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &, int);
	// 高精度数乘高精度数
	friend ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	// 高精度除以高精度
	friend ArbitraryPrecisionInteger operator/ (const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	// 求余数
	friend ArbitraryPrecisionInteger operator% (const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	void operator= (const ArbitraryPrecisionInteger &);
	void raw_output(ostream&) const;
};

#endif