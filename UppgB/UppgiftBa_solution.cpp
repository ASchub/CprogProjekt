/* Objekt av klassen Vector allokerar minne dynamiskt.
   Det beh�vs en destruktor som avallokerar minnet.
   F�r att objekt av denna klass ska kunna kopieras och
   tilldelas med v�rdesemantik beh�vs �ven en copy-konstruktor
   som allokerar nytt minne till sitt objekt och kopierar 
   v�rdena, samt en tilldelningsoperator som st�dar bort gammalt minne,
   allokerar nytt och kopierar v�rdena
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

// Destruktorn - st�dar bort dynamiskt allokerat minne
Vector::~Vector(){
  delete [] data;
}

// Copy-konstruktorn - initierar siz, allokerar minne, kopierar v�rdena
Vector::Vector(const Vector& other): siz(other.siz), data(new int[siz]){
  for(int i = 0; i < siz; ++i)
    data[i] = other.data[i];
}


// Tilldelningsoperatorn - returnerar referens till sitt objekt f�r att man
// ska kunna "kedja" tilldelningar, typ a = b = c;
const Vector& Vector::operator=(const Vector& other){
  if (this != &other){             // Test p� sj�lvtilldelning, a = a;
    delete [] data;                // St�da bort gammalt minne
    siz = other.siz;               // Tilldela siz
    data = new int[siz];           // Allokera nytt minne
    for(int i = 0; i < siz; ++i)   // Kopiera v�rdena
      data[i] = other.data[i];
  }
  return *this;                    // Returnera referens till eget objekt
}
