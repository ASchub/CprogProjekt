#include "Label.h"
#include "System.h"
using namespace std;

namespace cwing {


	Label::Label(int x, int y, const string& txt) : Labeled(x, y, txt)
	{
	}

	Label* Label::getInstance(int x, int y, const string& txt) {
		return new Label(x, y, txt);
	}

	void Label::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &getRect());
	}


	Label::~Label()
	{
	}

}