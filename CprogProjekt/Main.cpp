#include <SDL.h>
#include "GameEngine.h"
#include "StationarySprite.h"
#include "MovableSprite.h"
#include "AnimatedSprite.h"
#include "Hotkey.h"
#include <string>
#include "FunctionHotkey.h"
#include <iostream>
#include <memory>

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
	shared_ptr<StationarySprite> sSprite = StationarySprite::getInstance(100, 100, "./media/gubbe.bmp");
	shared_ptr<MovableSprite> mSprite = MovableSprite::getInstance(300, 100, "./media/gubbe.bmp");
	shared_ptr<AnimatedSprite> aSprite = AnimatedSprite::getInstance(500, 500, 14, 20, 7, "./media/flamesheet.bmp");

	shared_ptr<TestHotkey> h = shared_ptr<TestHotkey>(new TestHotkey());

	//hotkey testing, using SPACE, F, M
	//Hotkey* h = new TestHotkey();
	ge.add(h);

	//Hotkey* fh = FunctionHotkey::getInstance(SDLK_f, testFuncHotkey);
	shared_ptr<FunctionHotkey> fh = shared_ptr<FunctionHotkey>(FunctionHotkey::getInstance(SDLK_f, testFuncHotkey));
	ge.add(fh);
	//ge.setGravity(true, 1);w
	//sSprite->setAffectedByGravity(true); //testing Gravity

	ge.add(sSprite);
	ge.add(mSprite);
	ge.add(aSprite);
	ge.run();

	return 0;
}
