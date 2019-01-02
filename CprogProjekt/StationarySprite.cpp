#include "StationarySprite.h"
#include "System.h"
#include <iostream>

using namespace std;

namespace cwing {

	StationarySprite* StationarySprite::getInstance(int x, int y, const char path[]) {
		return new StationarySprite(x, y, path);
	}

	StationarySprite::StationarySprite(int x, int y, const char path[]) : Sprite(x, y, 0, 0, path)
	{
	}

	void StationarySprite::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &getRect());
	}

	void StationarySprite::handleCollision() {
		cout << "Stationary Sprite collided" << endl;
	}

} //cwing