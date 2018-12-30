/* Objekt av klassen Counted omsluter bara en std::string, som sköter
   sin egen värdesemantik, så det behövs ingen copy-konstruktor, 
   tilldelningsoperator eller destruktor för det.

   Men existerande objekt ska räknas. Det innebär att när objekt försvinner 
   så måste räknaren räknas ner. Dessutom kan objekt kopieras  och den 
   automatiskt genererade copy-konstruktorn kommer ju inte att räkna upp 
   räknaren så vi måste göra en copy-konstruktor också.

   Tilldelningsoperatorn däremot skapar inga nya objekt, den utför bara
   tilldelning mellan existerande objekt, så den automatiskt genererade
   tilldelningsoperatorn duger utmärkt.
*/

class Counted{
public:
  Counted(std::string d);
  Counted(const Counted& other);
  ~Counted();
  std::string get() const;
  static int getCount();
private:
  static int count;
  std::string data;
};

int Counted::count = 0;
Counted::Counted(std::string d):data(d){
  count++;
}
Counted::Counted(const Counted& other):data(other.data){
  count++;
}
Counted::~Counted(){
  count--;
}
std::string Counted::get() const { return data; }
int Counted::getCount() { return count; }
