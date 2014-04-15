#ifndef AUBITRARY_PRECISION_INTEGER
#define AUBITRARY_PRECISION_INTEGER

#include <vector>
#include <algorithm>
using namespace std;

class AubitraryPrecisionInteger {
private:
	bool negative;
	vector<int> digit;
	int length;

	void resetZero();
	bool isNegative() const;

	// �޷��żӷ�
	AubitraryPrecisionInteger add(const AubitraryPrecisionInteger &) const;
	// �޷��ż�������֤�����Ϊ����
	AubitraryPrecisionInteger sub(const AubitraryPrecisionInteger &) const;

public:
	AubitraryPrecisionInteger();
	AubitraryPrecisionInteger(int);
	AubitraryPrecisionInteger(const int &, const vector<int> &, bool);
	friend AubitraryPrecisionInteger operator+(const AubitraryPrecisionInteger&, const AubitraryPrecisionInteger&);
	friend bool operator<(const AubitraryPrecisionInteger &, const AubitraryPrecisionInteger &);
	friend bool operator>(const AubitraryPrecisionInteger &, const AubitraryPrecisionInteger &);
	friend AubitraryPrecisionInteger operator* (const AubitraryPrecisionInteger &, bool);
	friend AubitraryPrecisionInteger operator- (const AubitraryPrecisionInteger &);
	friend AubitraryPrecisionInteger operator- (const AubitraryPrecisionInteger &, const AubitraryPrecisionInteger &);
	// �������㣨ÿ����ζ��*10)
	friend AubitraryPrecisionInteger operator<< (const AubitraryPrecisionInteger &, int);
	void operator= (const AubitraryPrecisionInteger &);
	void raw_output(ostream&) const;
};

#endif