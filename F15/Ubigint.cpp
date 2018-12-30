#include "Ubigint.h"
using namespace std;

Ubigint::Ubigint(unsigned long int value) {
	// Rkna ut antal decimala siffror
	int size = 1;
	for (int v = value; (v /= 10)>0; size++)
		;
	// Skapa siffervektorn
	for (int i = 0; i<size; i++) {
		digits.push_back(value % 10);
		value /= 10;
	}
}

Ubigint::Ubigint(std::string value) {
	for (int i = value.length() - 1; i >= 0; i--)
		digits.push_back(value[i] - '0');
}

const Ubigint& Ubigint::operator+=(const Ubigint& right) {
	if (right.digits.size() > digits.size())
	digits.resize(right.digits.size());
	
	int minnet = 0;
	for (int i = 0; i<digits.size(); i++) {
		int rdig = (i<right.digits.size()) ? right.digits[i] : 0;
		int sum = digits[i] + rdig + minnet;
		minnet = sum / 10;
		digits[i] = sum % 10;
	}
	
	if (minnet != 0)
		digits.push_back(minnet);
	
	return *this;
}

const Ubigint Ubigint::operator+(const Ubigint& right) const {
	Ubigint tmp(*this);
	tmp += right;
	return tmp;
}

const Ubigint& Ubigint::operator++() {
	*this += 1;
	return *this;
}

const Ubigint Ubigint::operator++(int) {
	Ubigint tmp(*this);
	*this += 1;
	return tmp;
}

bool operator<(const Ubigint& left, const Ubigint& right) {
	if (left.digits.size() < right.digits.size())
		return true;
	else if (left.digits.size() > right.digits.size())
		return false;
	else {
		int i;
		for (i = left.digits.size() - 1; i >= 0 && left.digits[i] == right.digits[i]; i--)
			;
		if (i<0)
			return false;
		return left.digits[i] < right.digits[i];
	}

}

Ubigint::operator double() const {
	double tmp = 0.0;
	for (int i = digits.size() - 1; i >= 0; i--)
		tmp = tmp * 10 + digits[i];
	return tmp;
}

ostream& operator<<(ostream& os, const Ubigint& u) {
	for (int i = u.digits.size() - 1; i >= 0; --i)
		os << static_cast<char>(u.digits[i] + '0');
	return os;
}
























// operator<
//if (left.digits.size() < right.digits.size())
//	return true;
//else if (left.digits.size() > right.digits.size())
//return false;
//else {
//	int i;
//	for (i = left.digits.size() - 1; i >= 0 && left.digits[i] == right.digits[i]; i--)
//		;
//	if (i<0)
//		return false;
//	return left.digits[i] < right.digits[i];
//}
