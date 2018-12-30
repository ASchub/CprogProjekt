#ifndef UBIGINT_H
#define UBIGINT_H

#include <iostream>
#include <string>
#include <vector>

class Ubigint {
public:
	Ubigint(unsigned long int value = 0);
	explicit Ubigint(std::string value);
	const Ubigint& operator+=(const Ubigint& other);
	const Ubigint operator+(const Ubigint& right) const;
	const Ubigint& operator++();   // Prefix
    const Ubigint operator++(int);  // Postfix
	explicit operator double() const;
private:
	std::vector<char> digits;
	friend bool operator<(const Ubigint&, const Ubigint&);
	friend std::ostream& operator<<(std::ostream&, const Ubigint&);
};

std::ostream& operator<<(std::ostream& os, const Ubigint& right);

inline const Ubigint operator+(int left, const Ubigint& right) {
	return right + left;
}
bool operator<(const Ubigint& left, const Ubigint& right);
inline bool operator==(const Ubigint& left, const Ubigint& right) {
	return !(left < right) && !(right < left);
}
inline bool operator!=(const Ubigint& left, const Ubigint& right) {
	return !(left == right);
}
inline bool operator>(const Ubigint& left, const Ubigint& right) {
	return right < left;
}
inline bool operator<=(const Ubigint& left, const Ubigint& right) {
	return !(left > right);
}
inline bool operator>=(const Ubigint& left, const Ubigint& right) {
	return !(left < right);
}


#endif

