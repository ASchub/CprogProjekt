#ifndef ELEFANT_H
#define ELEFANT_H

#include <string>
#include "Animal.h"

namespace zoo{

  class Elefant : public Animal{
  public:
    Elefant(std::string n, int w, int t);
    int getTrunk() const;
  private:
    int trunk;
  };

  void printElefant(const Elefant* ele);

} // namespace zoo

#endif
