#include <SDL.h>
#include "GameEngine.h"
#include <string>
#include "StationarySprite.h"
#include "MovableSprite.h"
#include "AnimatedSprite.h"

using namespace std;
using namespace cwing;

int main(int argc, char** argv) {
	GameEngine ge;
	StationarySprite* sSprite = StationarySprite::getInstance(100, 100, "./media/gubbe.bmp");
	MovableSprite* mSprite = MovableSprite::getInstance(300, 100, "./media/gubbe.bmp");
	AnimatedSprite* aSprite = AnimatedSprite::getInstance(500,500, "./media/flamesheet.bmp");
	ge.add(sSprite);
	ge.add(mSprite);
	ge.add(aSprite);
	ge.run();
	return 0;
}