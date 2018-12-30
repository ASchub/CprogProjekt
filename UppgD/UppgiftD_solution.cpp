#include <string>

class Animal{
public:
  virtual ~Animal();
  std::string getName() const;
  int getWeight() const;

protected:
  Animal(std::string n, int w);                 // Förbjud skapande, 
                                                // tillåt subklasser
private:
  std::string name;
  int weight;

  Animal(const Animal& other);                  // Förbjud kopiering
  const Animal& operator=(const Animal& other); // Förbjud tilldelning
};

class Elephant : public Animal{
public:
  static Elephant* create(std::string n, int w, int tl);
  int getTrunkLength() const;
private:
  Elephant(std::string n, int w, int tl);       // Förbjud skapande, subklasser
  int trunkLength;
};

Elephant* Elephant::create(std::string n, int w, int tl){
  return new Elephant(n, w, tl);
}

Animal::Animal(std::string n, int w) : 
  name(n), weight(w) {}

Animal::~Animal() {}

std::string Animal::getName() const{
  return name;
}
int Animal::getWeight() const{
  return weight;
}
Elephant::Elephant(std::string n, int w, int tl)
  : Animal(n, w), trunkLength(tl){}

int Elephant::getTrunkLength() const{
  return trunkLength;
}

