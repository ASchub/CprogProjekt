#include <SDL.h>
#include "GameEngine.h"
#include <string>
#include "TestSprite.h"

using namespace std;
using namespace cwing;

int main(int argc, char** argv) {
	GameEngine ge;
	TestSprite* sprite = TestSprite::getInstance(100, 100, "f:/images/gubbe.bmp");
	ge.add(sprite);
	ge.run();
	return 0;
}