/* Objekt av klassen Counted omsluter bara en std::string, som sk�ter
   sin egen v�rdesemantik, s� det beh�vs ingen copy-konstruktor, 
   tilldelningsoperator eller destruktor f�r det.

   Men existerande objekt ska r�knas. Det inneb�r att n�r objekt f�rsvinner 
   s� m�ste r�knaren r�knas ner. Dessutom kan objekt kopieras  och den 
   automatiskt genererade copy-konstruktorn kommer ju inte att r�kna upp 
   r�knaren s� vi m�ste g�ra en copy-konstruktor ocks�.

   Tilldelningsoperatorn d�remot skapar inga nya objekt, den utf�r bara
   tilldelning mellan existerande objekt, s� den automatiskt genererade
   tilldelningsoperatorn duger utm�rkt.
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
