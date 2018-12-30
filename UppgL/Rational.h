#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream> // För att kunna deklarera operator<< och operator>>
#include <stdexcept>

class Rational{
public:
  // Ktor. Deklareras explicit för att undvika implicit konvertering
  // till Rational från int eller double
  explicit Rational(int n=0, int den=1);

  int get_num() const;                   // Täljarens värde
  int get_den() const;                   // Nämnarens värde
  int int_value() const;                 // Heltalsvärdet

  // Konvertering till double: vid operationer där Rational-objekt
  // blandas med double kommer Rational-objekten att omvandlas till
  // till double och det blir en double-operation
  operator double() const;
  operator double();

  // Aritmetiska operatorer
  // Unära
  const Rational& operator+() const;
  const Rational operator-() const;
  const Rational& operator++();
  const Rational operator++(int);
  const Rational& operator--();
  const Rational operator--(int);

  // Binära
  const Rational& operator+=(const Rational& right);
  const Rational operator+(const Rational& right) const;
  const Rational& operator-=(const Rational& right);
  const Rational operator-(const Rational& right) const;
  const Rational& operator*=(const Rational& right);
  const Rational operator*(const Rational& right) const;
  const Rational& operator/=(const Rational& right);
  const Rational operator/(const Rational& right) const;

private:
  int num, den;   // Täljaren, nämnaren
  void reduce();  // Förkortningsfunktionen

  friend bool operator==(const Rational& left, const Rational& right);
  friend bool operator<(const Rational& left, const Rational& right);
};


// Relationsoperatorer, övriga genereras från std::rel_ops-mallar
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
  
#include <utility>              // För rel_ops-mallar
using namespace std::rel_ops;   // Ge tillgång till mallar för övriga
                                // relationsoperatorer

#endif
