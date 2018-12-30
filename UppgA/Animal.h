#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

namespace zoo{

  class Animal{
  public:
    Animal(std::string n, int w);
    std::string getName() const;
    int getWeight() const;
  private:
    std::string name;
    int weight;
  };

} // namespace zoo

#endif
