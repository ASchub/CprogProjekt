#include <iostream>
#include "Elefant.h"

using namespace std;

namespace zoo{

  Elefant::Elefant(string n, int w, int t):Animal(n, w), trunk(t){}

  int Elefant::getTrunk() const{ 
    return trunk; 
  }

  void printElefant(const Elefant* ele){
    cout << ele->getName() << " " 
	 << ele->getWeight() << " " 
	 << ele->getTrunk() << endl;
  }

} // namespace zoo
