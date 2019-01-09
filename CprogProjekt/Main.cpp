#include <SDL.h>
#include "GameEngine.h"
#include "StationarySprite.h"
#include "MovableSprite.h"
#include "AnimatedSprite.h"
#include "Hotkey.h"

#include <string>
#include <iostream>
#include <memory>

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
	shared_ptr<StationarySprite> sSprite = StationarySprite::getInstance(100, 100, "./media/gubbe.bmp");
	shared_ptr<MovableSprite> mSprite = MovableSprite::getInstance(300, 100, "./media/gubbe.bmp");
	shared_ptr<AnimatedSprite> aSprite = AnimatedSprite::getInstance(500, 500, 14, 20, 7, "./media/flamesheet.bmp");

	shared_ptr<TestHotkey> h = shared_ptr<TestHotkey>(new TestHotkey());
	ge.add(h);

	//ge.setGravity(true, 1);
	//sSprite->setAffectedByGravity(true); //testing Gravity

	ge.add(sSprite);
	ge.add(mSprite);
	ge.add(aSprite);
	ge.run();

	return 0;
}