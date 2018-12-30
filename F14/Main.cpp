// Tillämpning

#include <SDL.h>
#include <SDL_mixer.h>
#include "Session.h"
#include "Label.h"
#include "Button.h"
#include "FuncButton.h"
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

void pause(const string&) {
	Mix_Pause(-1);
}

void resume(const string&) {
	Mix_Resume(-1);
}

int main(int argc, char** argv) {
	Session ses;

	Button* b = new MyButton(ses);
	ses.add(b);

	Button* fb1 = FuncButton::getInstance(100, 300, "Pausa", pause);
	ses.add(fb1);
	Button* fb2 = FuncButton::getInstance(100, 400, "Resume", resume);
	ses.add(fb2);
	ses.run();
	return 0;
}