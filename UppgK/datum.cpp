#include "datum.h"
#include <stdexcept>
using namespace std;

const int Datum::MAXDAG[]={31,28,31,30,31,30,31,31,30,31,30,31};

Datum::Datum(int d, int m){
  if (m < 1 || m > 12 || d < 1 || d > MAXDAG[m-1])
    throw std::invalid_argument("Fel");
  for(dagnr = 0; m-1 > 0; m--)
    dagnr += MAXDAG[m-2];
  dagnr += d;
}

const Datum& Datum::operator+=(int antal){
  dagnr += antal;
  if (dagnr > 365)
    throw std::out_of_range("Fel");
  return *this;
}

const Datum Datum::operator+(int antal) const{
  Datum tmp(*this);
  tmp += antal;
  return tmp;
}

const Datum& Datum::operator++(){
  return *this += 1;
}

const Datum Datum::operator++(int){
  Datum tmp(*this);
  *this += 1;
  return tmp;
}

int Datum::operator-(const Datum& other) const{
  return dagnr - other.dagnr;
}

bool Datum::operator==(const Datum& rhs) const{
  return dagnr == rhs.dagnr;
}

bool Datum::operator<(const Datum& rhs) const{
  return dagnr < rhs.dagnr;
}

std::ostream& operator<<(ostream& os, const Datum& datum){
  int m = 0, d = 0;
  for(m=0; d < datum.dagnr; m++)
    d += Datum::MAXDAG[m];  
  int dag = datum.dagnr - d + Datum::MAXDAG[m-1];
  return os << dag << "/" << m;
}
