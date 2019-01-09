#include <SDL.h>
#include "GameEngine.h"
#include "StationarySprite.h"
#include "MovableSprite.h"
#include "AnimatedSprite.h"
#include "Hotkey.h"
#include <string>
#include "FunctionHotkey.h"
#include "MemberHotkey.h"
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
	//shared_ptr<MovableSprite> mSprite = MovableSprite::getInstance(500, 100, "./media/gubbe.bmp");
	shared_ptr<AnimatedSprite> aSprite = AnimatedSprite::getInstance(500, 500, 14, 20, 7, "./media/flamesheet.bmp");

	//Testing player controlled Movable with memberhotkeys
	shared_ptr<MovableSprite> pcSprite = MovableSprite::getInstance(300, 100, "./media/gubbe.bmp");
	ge.add(pcSprite);

	shared_ptr<MemberHotkey<MovableSprite>> upKey = MemberHotkey<MovableSprite>::getInstance(SDLK_UP, pcSprite, &MovableSprite::moveUp);
	shared_ptr<MemberHotkey<MovableSprite>> downKey = MemberHotkey<MovableSprite>::getInstance(SDLK_DOWN, pcSprite, &MovableSprite::moveDown);
	shared_ptr<MemberHotkey<MovableSprite>> rightKey = MemberHotkey<MovableSprite>::getInstance(SDLK_RIGHT, pcSprite, &MovableSprite::moveRight);
	shared_ptr<MemberHotkey<MovableSprite>> leftKey = MemberHotkey<MovableSprite>::getInstance(SDLK_LEFT, pcSprite, &MovableSprite::moveLeft);

	ge.add(upKey);
	ge.add(downKey);
	ge.add(rightKey);
	ge.add(leftKey);

	//hotkey testing, using SPACE, F, M
	//Hotkey* h = new TestHotkey();
	shared_ptr<TestHotkey> h = shared_ptr<TestHotkey>(new TestHotkey());
	ge.add(h);

	//Hotkey* fh = FunctionHotkey::getInstance(SDLK_f, testFuncHotkey);
	shared_ptr<FunctionHotkey> fh = FunctionHotkey::getInstance(SDLK_f, testFuncHotkey);
	ge.add(fh);

	shared_ptr<MemberHotkey<Hotkey>> mh = MemberHotkey<Hotkey>::getInstance(SDLK_m, fh, &Hotkey::perform);
	ge.add(mh);

	//ge.setGravity(true, 1);
	//sSprite->setAffectedByGravity(true); //testing Gravity

	ge.add(sSprite);
	//ge.add(mSprite);
	ge.add(aSprite);
	ge.run();

	return 0;
}
