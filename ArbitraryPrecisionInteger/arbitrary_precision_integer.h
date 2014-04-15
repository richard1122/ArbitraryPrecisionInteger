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

	// �޷��żӷ�
	ArbitraryPrecisionInteger add(const ArbitraryPrecisionInteger &) const;
	// �޷��ż�������֤�����Ϊ����
	ArbitraryPrecisionInteger sub(const ArbitraryPrecisionInteger &) const;
	// �߾���������������֤��������
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
	// �������㣨ÿ����ζ��*10)
	friend ArbitraryPrecisionInteger operator<< (const ArbitraryPrecisionInteger &, int);
	// �߾������˵;�����
	friend ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &, int);
	// �߾������˸߾�����
	friend ArbitraryPrecisionInteger operator* (const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	// �߾��ȳ��Ը߾���
	friend ArbitraryPrecisionInteger operator/ (const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	// ������
	friend ArbitraryPrecisionInteger operator% (const ArbitraryPrecisionInteger &, const ArbitraryPrecisionInteger &);
	void operator= (const ArbitraryPrecisionInteger &);
	void raw_output(ostream&) const;
};

#endif