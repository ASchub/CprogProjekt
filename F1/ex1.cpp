/* ex1.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Animal{
  char* name;
  int tailLength;
};

Animal* newAnimal(const char* aName, int aTail){
  Animal* tmp = (Animal*)malloc(sizeof(Animal));
  tmp->name = (char*)malloc(strlen(aName) + 1);
  strcpy(tmp->name, aName);
  tmp->tailLength = aTail;
  return tmp;
}

char* getName(Animal* animal){
  return animal->name;
}

int main(){
  Animal* zoo[3];
  int i;

  zoo[0] = newAnimal("Rex", 30);
  zoo[1] = newAnimal("Pippi", 2);
  zoo[2] = newAnimal("Sokrates", 7);

  for(i = 0; i < 3; i++)
    printf("%s\n", getName(zoo[i]));

  for(i = 0; i < 3; i++){
    free(zoo[i]->name);
    free(zoo[i]);
  }

  return 0;
}
