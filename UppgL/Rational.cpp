#include "Rational.h"
using namespace std;

void Rational::reduce(){
  int sign=1;
  if (num < 0){
    sign = -1;
    num = -num;
  }
  if (den < 0){
    sign = -sign;
    den = -den;
  }
  int gcd=num;
  int d=den;
  while(d!=0){
    int tmp = gcd % d;
    gcd = d;
    d = tmp;
  }
  num /= gcd;
  num *= sign;
  den /= gcd;
} // reduce

Rational::Rational(int n, int d):num(n), den(d){
  if (d==0)
    throw std::invalid_argument("Error constructing Rational");
  reduce();
}

const Rational Rational::operator-() const{
  return Rational(-num, den);
}

const Rational& Rational::operator+=(const Rational& right){
  num = num * right.den + right.num * den;
  den *= right.den;
  reduce();
  return *this;
}

const Rational Rational::operator+(const Rational& right) const{
  Rational tmp(*this);
  tmp+=right;
  return tmp;
}

const Rational& Rational::operator++(){
  *this+=Rational(1);
  reduce();
  return *this;
}

const Rational Rational::operator++(int){
  Rational tmp(*this);
  ++*this;
  return tmp;
}

const Rational& Rational::operator-=(const Rational& right){
  return *this+=-right;
}

const Rational Rational::operator-(const Rational& right) const{
  Rational tmp(*this);
  tmp-=right;
  return tmp;
}

const Rational& Rational::operator--(){
  *this-=Rational(1);
  reduce();
  return *this;
}

const Rational Rational::operator--(int){
  Rational tmp(*this);
  --*this;
  return tmp;
}

const Rational& Rational::operator*=(const Rational& right){
  den*=right.den;
  num*=right.num;
  reduce();
  return *this;
}

const Rational Rational::operator*(const Rational& right) const{
  Rational tmp(*this);
  tmp*=right;
  return tmp;
}

const Rational& Rational::operator/=(const Rational& right){
  den*=right.num;
  num*=right.den;
  reduce();
  return *this;
}

const Rational Rational::operator/(const Rational& right) const{
  Rational tmp(*this);
  tmp/=right;
  return tmp;
}

bool operator==(const Rational& left, const Rational& right){
  return left.den == right.den && left.num == right.num;
}

bool operator<(const Rational& left, const Rational& right){
  return left.num * right.den < left.den * right.num;
}

ostream& operator<<(ostream& os, const Rational& rat){
  return os << rat.get_num() << '/' << rat.get_den();
}

std::istream& operator>>(std::istream& is, Rational& rat){
  int n, d;
  if (is >> n){
    char sep;
    is >> sep >> d;
    if (is && sep=='/')
      rat = Rational(n, d);
    else
      is.clear(ios_base::badbit);
  }
  return is;
}

