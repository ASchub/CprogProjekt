#include <SDL.h>
#include "GameEngine.h"
#include <string>
#include "StationarySprite.h"
#include "MovableSprite.h"

using namespace std;
using namespace cwing;

int main(int argc, char** argv) {
	GameEngine ge;
	StationarySprite* sSprite = StationarySprite::getInstance(100, 100, "./media/gubbe.bmp");
	MovableSprite* mSprite = MovableSprite::getInstance(200, 200, "./media/gubbe.bmp");
	ge.add(sSprite);
	ge.add(mSprite);
	ge.run();
	return 0;
}