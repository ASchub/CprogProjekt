#include <SDL.h>
#include "GameEngine.h"
#include <string>
#include "StationarySprite.h"
#include "MovableSprite.h"
#include "AnimatedSprite.h"
#include "Hotkey.h"
#include <iostream>

using namespace std;
using namespace cwing;

class TestHotkey : public Hotkey{
public:
	TestHotkey() :Hotkey(SDLK_SPACE) {}
	void perform() {
		cout << "Hotkey working!" << endl;
	}
};

int main(int argc, char** argv) {
	GameEngine ge;
	StationarySprite* sSprite = StationarySprite::getInstance(100, 100, "./media/gubbe.bmp");
	MovableSprite* mSprite = MovableSprite::getInstance(300, 100, "./media/gubbe.bmp");
	AnimatedSprite* aSprite = AnimatedSprite::getInstance(500,500, "./media/flamesheet.bmp");

	Hotkey* h = new TestHotkey();
	ge.add(h);

	ge.add(sSprite);
	ge.add(mSprite);
	ge.add(aSprite);
	ge.run();
	return 0;
}