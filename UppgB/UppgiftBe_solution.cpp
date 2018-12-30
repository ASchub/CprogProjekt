/* Copy-konstruktor behövs för att räkna upp räknaren för värdet när det nytt objekt 
   skapas ur ett existerande, destruktor för att räkna ner motsvarande räknare.
   Vid tilldelning ändras ju värdet i ett objekt till ett värde som finns i ett annat,
   så räknaren för det gamla värdet måste räknas ner och räknaren för det tilldelade
   värdet måste räknas upp - tilldelningsoperatorn behövs alltså också.
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

Valued::Valued(std::string str):data(str){ values[str]++; // Blir 1 första gången
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
  if (data != other.data){  // Obs! annat villkor för "självtilldelning"
    if (--values[data] == 0)
      values.erase(data);
    data = other.data;
    values[data]++;
  }
  return *this;
}

