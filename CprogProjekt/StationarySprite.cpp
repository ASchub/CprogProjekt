#include "StationarySprite.h"
#include "System.h"

#include <iostream>
#include <memory>

using namespace std;

namespace cwing {

	shared_ptr<StationarySprite> StationarySprite::getInstance(int x, int y, const char path[]) {
		return shared_ptr<StationarySprite>(new StationarySprite(x, y, path));
	}

	StationarySprite::StationarySprite(int x, int y, const char path[]) : Sprite(x, y, 0, 0, path)
	{
	}

	void StationarySprite::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, getRect().get());
	}


} //cwing