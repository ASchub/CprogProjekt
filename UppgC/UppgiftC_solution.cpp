/* F�r att kontrollera objektskapandet - t.ex. som h�r se till att
   objekten endast f�r skapas dynamiskt - m�ste man g�ra alla konstruktorer
   privata (eller protected om man vill till�ta subklasser) och ist�llet
   g�ra fabriksfunktioner (statiska medlemsfunktioner eller friend-deklarerade
   fria funktioner).
   Man f�r d� inte gl�mma copy-konstruktorn: g�r man inget s� kommer 
   kompilatorn att generera en publik copy-konstruktor och d�rmed till�ta
   skapande av objekt p� annat s�tt �n dynamiskt.

   F�r att endast till�ta tio objekt m�ste man r�kna objekten.
   F�r det beh�vs en statisk variabel som r�knas upp i konstruktorer och
   r�knas ner i destruktorn. I konstruktorerna kan man d� testa denna 
   variabel och om den har blivit tio s� genererar man ett undantag.
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
    throw std::out_of_range("F�r m�nga objekt!");
  count++;
}

TenAtMost::TenAtMost(std::string str):name(str){
  if (count == 10)
    throw std::out_of_range("F�r m�nga objekt!");
  count++;
}

std::string TenAtMost::getName() const{
  return name;
}

