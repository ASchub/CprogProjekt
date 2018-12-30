#include <string>
#include <iostream>
using namespace std;

class Animal {
public:
	string get_name() const { return name; }
	virtual void moves() const { cout << "Springer"; }
	virtual void talks() const = 0;
	virtual ~Animal() {}
protected:
	Animal(string n) :name(n) {}
private:
	string name;
	Animal(const Animal&) = delete;
	const Animal& operator=(const Animal&) = delete;
};

class Wing {

};

class Bird : public Animal {
public:
	static Bird* create(string n, double ws);
	double get_wingspan() const { return wingspan; }
	void moves() const { cout << "Flyger";  }
	void talks() const { cout << "Kvitter kvitter"; }
	~Bird() { delete left; delete right; }
private:
	double wingspan;
	Wing *left, *right;
	Bird(string n, double ws) :Animal(n), wingspan(ws), left(new Wing), right(new Wing){}
};

Bird* Bird::create(string n, double ws) {
	return new Bird(n, ws);
}

class Cat : public Animal {
public:
	static Cat* create(string n, bool d);
	int get_lives() const { return lives; }
	bool is_domestic() const { return domestic; }
	void talks() const { cout << "Mjau mjau"; }
private:
	Cat(string n, bool d) :Animal(n), lives(9), domestic(d) {}
	int lives;
	bool domestic;
};

Cat* Cat::create(string n, bool d) {
	return new Cat(n, d);
}

#include <vector>

int main() {
	vector<Animal*> zoo;

	zoo.push_back(Bird::create("Pippi", 2.5));
	zoo.push_back(Cat::create("Simba", false));

	double summa = 0;
	int count_birds = 0;
	for (Animal* a : zoo) {
		if (Bird* b = dynamic_cast<Bird*>(a)) {
			summa += b->get_wingspan();
			count_birds++;
		}
	}
	
	cout << "Genomsnittlig vingbredd: " << summa / count_birds << endl;

}