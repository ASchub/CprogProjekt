#include <SDL.h>
#include "Label.h"
#include "GameEngine.h"
#include "Button.h"
#include <string>
using namespace std;
using namespace cwing;

Label* lbl;

class MyButton : public Button {
public:
	MyButton() :Button(50, 100, "Ok") {}
	void perform(const string& txt) {
		lbl->setText("Stefan");
	}
};

int main(int argc, char** argv) {
	GameEngine ge;

	lbl = Label::getInstance(100, 100, "Jozef");
	ge.add(lbl);

	Button* b = new MyButton();
	ge.add(b);
	ge.run();
	return 0;
}