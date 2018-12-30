#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream> // F�r att kunna deklarera operator<< och operator>>
#include <stdexcept>

class Rational{
public:
  // Ktor. Deklareras explicit f�r att undvika implicit konvertering
  // till Rational fr�n int eller double
  explicit Rational(int n=0, int den=1);

  int get_num() const;                   // T�ljarens v�rde
  int get_den() const;                   // N�mnarens v�rde
  int int_value() const;                 // Heltalsv�rdet

  // Konvertering till double: vid operationer d�r Rational-objekt
  // blandas med double kommer Rational-objekten att omvandlas till
  // till double och det blir en double-operation
  operator double() const;
  operator double();

  // Aritmetiska operatorer
  // Un�ra
  const Rational& operator+() const;
  const Rational operator-() const;
  const Rational& operator++();
  const Rational operator++(int);
  const Rational& operator--();
  const Rational operator--(int);

  // Bin�ra
  const Rational& operator+=(const Rational& right);
  const Rational operator+(const Rational& right) const;
  const Rational& operator-=(const Rational& right);
  const Rational operator-(const Rational& right) const;
  const Rational& operator*=(const Rational& right);
  const Rational operator*(const Rational& right) const;
  const Rational& operator/=(const Rational& right);
  const Rational operator/(const Rational& right) const;

private:
  int num, den;   // T�ljaren, n�mnaren
  void reduce();  // F�rkortningsfunktionen

  friend bool operator==(const Rational& left, const Rational& right);
  friend bool operator<(const Rational& left, const Rational& right);
};


// Relationsoperatorer, �vriga genereras fr�n std::rel_ops-mallar
bool operator==(const Rational& left, const Rational& right);
bool operator<(const Rational& left, const Rational& right);

// Deklarationer av operator<< och operator>>
  
// operator>> ingick inte i uppgiften men borde ju finnas med
  
std::ostream& operator<<(std::ostream&, const Rational&);
std::istream& operator>>(std::istream&, Rational&);


inline int Rational::int_value() const{
  return num/den;
}
  
inline int Rational::get_num() const{
  return num;
}
  
inline int Rational::get_den() const{
  return den;
}
  
inline const Rational& Rational::operator+() const{
  return *this;
}
  
#include <utility>              // F�r rel_ops-mallar
using namespace std::rel_ops;   // Ge tillg�ng till mallar f�r �vriga
                                // relationsoperatorer

#endif
