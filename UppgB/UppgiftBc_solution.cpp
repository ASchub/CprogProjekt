/* Objekt av klassen Managed omsluter bara en std::string, som sk�ter
   sin egen v�rdesemantik, s� det beh�vs ingen copy-konstruktor, 
   tilldelningsoperator eller destruktor f�r det.

   Men varje objekt som existerar ska ju pekas ut fr�n den statiska
   vektorn objects. Det inneb�r att n�r objekt f�rsvinner s� m�ste de tas
   bort fr�n vektorn, vilket borde g�ras i destruktorn.
   Dessutom kan objekt kopieras  och den automatiskt genererade
   copy-konstruktorn kommer ju inte att s�tta n�gon pekare till det nya
   objektet i vektorn, s� vi m�ste g�ra en copy-konstruktor ocks�.

   Tilldelningsoperatorn d�remot skapar inga nya objekt, den utf�r bara
   tilldelning mellan existerande objekt, s� den automatiskt genererade
   tilldelningsoperatorn duger utm�rkt.
*/

class Managed{
  static std::vector<Managed*> objects;    // Endast deklaration
  std::string data;
public:
  Managed(std::string d): data(d){ 
    objects.push_back(this); 
  }

  Managed(const Managed& other):data(other.data){
    objects.push_back(this);
  }

  std::string get_data() const { 
    return data; 
  }

  ~Managed();  // Deklaration, definitionen stor s� utanf�r

}; // Managed

std::vector<Managed*> Managed::objects;    // Definition

Managed::~Managed(){
  for(int i = 0; i < objects.size(); ++i)
    if (objects[i] == this) {
      objects.erase(objects.begin() + i);
      break;
    }
}
