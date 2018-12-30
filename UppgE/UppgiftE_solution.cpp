#include <vector>

class Mat {
public:
  int getVikt() const { return vikt; }
  int getSotma() const { return sotma; }
  virtual int getNaring() const = 0;
  virtual ~Mat(){}
protected:
  Mat(int v, int s):vikt(v), sotma(s){}
private:
  int vikt, sotma;
  Mat(const Mat& other);
  const Mat& operator=(const Mat& other);
};

class Myrstack : public Mat{
public:
  static Myrstack* getInstance(int v, int m);
  int getMyror() const { return myror; }
  int getNaring() const { return getVikt() + myror; }
private:
  int myror;
  Myrstack(int v, int m) : Mat(v, 0), myror(m){}
};

Myrstack* Myrstack::getInstance(int v, int m){
  return new Myrstack(v, m);
}

class Blabar : public Mat{
public:
  static Blabar* getInstance(int v, int s, int y);
  int getYta() const { return yta; }
  int getNaring() const { return getVikt() / yta; }
private:
  Blabar(int v, int s, int y):Mat(v,s), yta(y){}
  int yta;
};

Blabar* Blabar::getInstance(int v, int s, int y){
  return new Blabar(v, s, y);
}

class Getingbo : public Mat {
public:
  static Getingbo* getInstance(int v, bool h);
  bool hasHonung() const { return honung; }
  int getNaring() const { 
    //    return (honung)?getVikt()*2 : getVikt()/2;
    if (honung)
      return getVikt() * 2;
    else
      return getVikt() / 2;
  }
private:
  Getingbo(int v, bool h):Mat(v, (h)?10:4), honung(h){}
  bool honung;
};

Getingbo* Getingbo::getInstance(int v, bool h){
  return new Getingbo(v, h);
}

class Bjorn {
public:
  int getVikt() const { return vikt; }
  void eats(std::vector<Mat*>& maten);
  virtual ~Bjorn() {}
protected:
  virtual bool likes(Mat* m) const { return true; }
  Bjorn(int v):vikt(v){}
private:
  int vikt;
  Bjorn(const Bjorn& other);
  const Bjorn& operator=(const Bjorn& other);
};

void Bjorn::eats(std::vector<Mat*>& maten){
  Mat* tyngst = NULL;
  int tyngstIndex;

  for(int i=0; i < maten.size(); ++i){
    if (likes(maten[i]) && (tyngst == NULL || 
	   tyngst->getVikt() < maten[i]->getVikt())){
      tyngst = maten[i];
      tyngstIndex = i;
    } // if
  } // for

  if (tyngst != NULL){
    vikt += tyngst->getNaring() / 4;
    maten.erase(maten.begin() + tyngstIndex);
    delete tyngst;
  }
}

class Grizzly : public Bjorn {
public:
  static Grizzly* getInstance(int v);
protected:
  bool likes(Mat* m) const {
    if (dynamic_cast<Myrstack*>(m) == NULL)
      return false;
    else
      return true;
  }
private:
  Grizzly(int v):Bjorn(v){}
};

Grizzly* Grizzly::getInstance(int v){
  return new Grizzly(v);
}

class Panda : public Bjorn {
public:
  static Panda* getInstance(int v);
protected:
  bool likes(Mat* m) const { return m->getSotma() > 6; }
private:
  Panda(int v):Bjorn(v){}
};

Panda* Panda::getInstance(int v){
  return new Panda(v);
}

class Brun : public Bjorn {
public:
  static Brun* getInstance(int v);
private:
  Brun(int v):Bjorn(v){}
};

Brun* Brun::getInstance(int v){
  return new Brun(v);
}
