#include <SDL.h>
#include "GameEngine.h"
#include <string>
#include "StationarySprite.h"
#include "MovableSprite.h"
#include "AnimatedSprite.h"
#include "Hotkey.h"
#include "FunctionHotkey.h"
#include <iostream>

using namespace std;
using namespace cwing;

class TestHotkey : public Hotkey{
public:
	TestHotkey() :Hotkey(SDLK_SPACE) {}
	void perform() {
		cout << "Normal Hotkey working!" << endl;
	}
};

void testFuncHotkey() {
	cout << "Function Hotkey Working!" << endl;
}

int main(int argc, char** argv) {
	GameEngine ge;
	StationarySprite* sSprite = StationarySprite::getInstance(100, 100, "./media/gubbe.bmp");
	MovableSprite* mSprite = MovableSprite::getInstance(300, 100, "./media/gubbe.bmp");
	AnimatedSprite* aSprite = AnimatedSprite::getInstance(500, 500, 14, 20, 7, "./media/flamesheet.bmp");

	//hotkey testing, using SPACE, F, M
	Hotkey* h = new TestHotkey();
	ge.add(h);

	Hotkey* fh = FunctionHotkey::getInstance(SDLK_f, testFuncHotkey);
	ge.add(fh);

	//ge.setGravity(true, 1);
	//sSprite->setAffectedByGravity(true); //testing Gravity

	ge.add(sSprite);
	ge.add(mSprite);
	ge.add(aSprite);
	ge.run();
	return 0;
}
