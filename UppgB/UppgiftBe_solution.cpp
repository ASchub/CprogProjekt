/* Copy-konstruktor beh�vs f�r att r�kna upp r�knaren f�r v�rdet n�r det nytt objekt 
   skapas ur ett existerande, destruktor f�r att r�kna ner motsvarande r�knare.
   Vid tilldelning �ndras ju v�rdet i ett objekt till ett v�rde som finns i ett annat,
   s� r�knaren f�r det gamla v�rdet m�ste r�knas ner och r�knaren f�r det tilldelade
   v�rdet m�ste r�knas upp - tilldelningsoperatorn beh�vs allts� ocks�.
*/

#include <map>
#include <string>

class Valued{
public:
  Valued(std::string str);
  Valued(const Valued& other);
  const Valued& operator=(const Valued& other);
  ~Valued();
  static std::map<std::string,int>& getValues();
private:
  std::string data;
  static std::map<std::string, int> values;
};

std::map<std::string, int> Valued::values;

Valued::Valued(std::string str):data(str){ values[str]++; // Blir 1 f�rsta g�ngen
}

std::map<std::string,int>& Valued::getValues(){ return values;
}

Valued::Valued(const Valued& other):data(other.data){
  values[data]++;
}

Valued::~Valued(){
  if(--values[data] == 0)
    values.erase(data);
}

const Valued& Valued::operator=(const Valued& other){
  if (data != other.data){  // Obs! annat villkor f�r "sj�lvtilldelning"
    if (--values[data] == 0)
      values.erase(data);
    data = other.data;
    values[data]++;
  }
  return *this;
}

