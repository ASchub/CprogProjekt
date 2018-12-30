#include <string>

class Wrapper_base{
public:
  virtual void show() const = 0;
  virtual ~Wrapper_base(){}
};

template <typename TYP>
class Wrapper:public Wrapper_base{
public:
  Wrapper(TYP init):data(init){}
  TYP get() const { return data; }
  void set(TYP nyData) { data = nyData; }
  void show() const { cout << data; }
private:
  TYP data;
};

typedef Wrapper<std::string> Namn;
typedef Wrapper<int> Nummer;
typedef Wrapper<double> Matvarde;

