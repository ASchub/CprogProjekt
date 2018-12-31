#include <SDL.h>
#include "GameEngine.h"
#include <string>
#include "StationarySprite.h"

using namespace std;
using namespace cwing;

int main(int argc, char** argv) {
	GameEngine ge;
	StationarySprite* sprite = StationarySprite::getInstance(100, 100, "../media/gubbe.bmp");
	ge.add(sprite);
	ge.run();
	return 0;
}