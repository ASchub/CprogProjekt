/* Objekt av klassen Managed omsluter bara en std::string, som sköter
   sin egen värdesemantik, så det behövs ingen copy-konstruktor, 
   tilldelningsoperator eller destruktor för det.

   Men varje objekt som existerar ska ju pekas ut från den statiska
   vektorn objects. Det innebär att när objekt försvinner så måste de tas
   bort från vektorn, vilket borde göras i destruktorn.
   Dessutom kan objekt kopieras  och den automatiskt genererade
   copy-konstruktorn kommer ju inte att sätta någon pekare till det nya
   objektet i vektorn, så vi måste göra en copy-konstruktor också.

   Tilldelningsoperatorn däremot skapar inga nya objekt, den utför bara
   tilldelning mellan existerande objekt, så den automatiskt genererade
   tilldelningsoperatorn duger utmärkt.
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

  ~Managed();  // Deklaration, definitionen stor så utanför

}; // Managed

std::vector<Managed*> Managed::objects;    // Definition

Managed::~Managed(){
  for(int i = 0; i < objects.size(); ++i)
    if (objects[i] == this) {
      objects.erase(objects.begin() + i);
      break;
    }
}
