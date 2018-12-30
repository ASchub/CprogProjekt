/* Objekt av klassen Vector allokerar minne dynamiskt.
   Det behövs en destruktor som avallokerar minnet.
   För att objekt av denna klass ska kunna kopieras och
   tilldelas med värdesemantik behövs även en copy-konstruktor
   som allokerar nytt minne till sitt objekt och kopierar 
   värdena, samt en tilldelningsoperator som städar bort gammalt minne,
   allokerar nytt och kopierar värdena
*/

class Vector{
  int siz;
  int* data;
public:
  Vector(int n):siz(n), data(new int[siz]){}
  int& operator[](int index) { return data[index]; }


  Vector(const Vector& other);                    // Copy-ktor
  const Vector& operator=(const Vector& other);   // Tilldelningsoperator
  ~Vector();                                      // Destruktor
}; // Vector

// Definitioner

// Destruktorn - städar bort dynamiskt allokerat minne
Vector::~Vector(){
  delete [] data;
}

// Copy-konstruktorn - initierar siz, allokerar minne, kopierar värdena
Vector::Vector(const Vector& other): siz(other.siz), data(new int[siz]){
  for(int i = 0; i < siz; ++i)
    data[i] = other.data[i];
}


// Tilldelningsoperatorn - returnerar referens till sitt objekt för att man
// ska kunna "kedja" tilldelningar, typ a = b = c;
const Vector& Vector::operator=(const Vector& other){
  if (this != &other){             // Test på självtilldelning, a = a;
    delete [] data;                // Städa bort gammalt minne
    siz = other.siz;               // Tilldela siz
    data = new int[siz];           // Allokera nytt minne
    for(int i = 0; i < siz; ++i)   // Kopiera värdena
      data[i] = other.data[i];
  }
  return *this;                    // Returnera referens till eget objekt
}
