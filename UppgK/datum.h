#ifndef DATUM_H
#define DATUM_H
#include <iostream>

class Datum{
public:
  Datum(int d, int m);
  const Datum& operator+=(int antal);
  const Datum operator+(int antal) const;
  const Datum& operator++();
  const Datum operator++(int);
  int operator-(const Datum& other) const;
  bool operator==(const Datum& rhs) const;
  bool operator<(const Datum& rhs) const;
private:
  int dagnr;
  static const int MAXDAG[];
  friend std::ostream& operator<<(std::ostream&, const Datum&);
};

inline const Datum operator+(int antal, const Datum& d){
  return d + antal;
}

#include <utility>
using namespace std::rel_ops;

#endif
