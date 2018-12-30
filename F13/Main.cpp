// Tillämpning

#include <SDL.h>
#include "Session.h"
#include "Label.h"
#include "Button.h"
#include <string>
using namespace std;
using namespace cwing;

Label* lbl;

class MyButton : public Button {
public:
	MyButton(Session& s) :Button(50, 100, "Ok"), ses(s) {}
	void perform(const string& txt) {
		if (added) {
			ses.remove(lbl);
			added = false;
		}
		else {
			lbl = Label::getInstance(100, 100, "Jozef");
			ses.add(lbl);
			added = true;
		}
	}
private:
	bool added = false;
	Session& ses;
};

int main(int argc, char** argv) {
	Session ses;

	Button* b = new MyButton(ses);
	ses.add(b);
	ses.run();
	return 0;
}