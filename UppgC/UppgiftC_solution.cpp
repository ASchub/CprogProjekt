/* För att kontrollera objektskapandet - t.ex. som här se till att
   objekten endast får skapas dynamiskt - måste man göra alla konstruktorer
   privata (eller protected om man vill tillåta subklasser) och istället
   göra fabriksfunktioner (statiska medlemsfunktioner eller friend-deklarerade
   fria funktioner).
   Man får då inte glömma copy-konstruktorn: gör man inget så kommer 
   kompilatorn att generera en publik copy-konstruktor och därmed tillåta
   skapande av objekt på annat sätt än dynamiskt.

   För att endast tillåta tio objekt måste man räkna objekten.
   För det behövs en statisk variabel som räknas upp i konstruktorer och
   räknas ner i destruktorn. I konstruktorerna kan man då testa denna 
   variabel och om den har blivit tio så genererar man ett undantag.
*/

#include <string>
#include <stdexcept>

class TenAtMost{
public:
  static TenAtMost* create(std::string n);
  static TenAtMost* create(const TenAtMost& other);

  std::string getName() const;
  ~TenAtMost(){ count--; }
private:
  TenAtMost(std::string n);
  TenAtMost(const TenAtMost& other);
  std::string name;
  static int count; // Deklaration
};

int TenAtMost::count = 0;  // Definition

TenAtMost* TenAtMost::create(std::string str){
  return new TenAtMost(str);
}

TenAtMost* TenAtMost::create(const TenAtMost& other){
  return new TenAtMost(other);
}

TenAtMost::TenAtMost(const TenAtMost& other) : name(other.name){
  if (count == 10)
    throw std::out_of_range("För många objekt!");
  count++;
}

TenAtMost::TenAtMost(std::string str):name(str){
  if (count == 10)
    throw std::out_of_range("För många objekt!");
  count++;
}

std::string TenAtMost::getName() const{
  return name;
}

