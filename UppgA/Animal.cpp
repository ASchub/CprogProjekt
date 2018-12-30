#include "Animal.h"

using namespace std;

namespace zoo{

  Animal::Animal(string n, int w):name(n), weight(w){}
  string Animal::getName() const{ 
    return name; 
  }

  int Animal::getWeight() const{ 
    return weight; 
  }

} // namespace zoo
