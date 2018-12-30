// ex2.cpp

#include <iostream>
#include <string>

using namespace std;

class Animal{
private:
  string name;
  int tailLength;
public:
  Animal(string aName, int aTail){
    name = aName;
    tailLength = aTail;
  }
  string getName(){
    return name;
  }
  int getTailLength(){
    return tailLength;
  }
};

int main( int argc, char *argv[] ){
  Animal* zoo[3];

  zoo[0] = new Animal("Rex", 30);
  zoo[1] = new Animal("Pippi", 2);
  zoo[2] = new Animal("Sokrates", 7);


  for(int i = 0; i < 3; i++)
    cout << zoo[i]->getName() << endl;

  for(int i = 0; i < 3; i++)
    delete zoo[i];

  return 0;
}
