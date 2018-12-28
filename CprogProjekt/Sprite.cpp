#include "Sprite.h"

namespace cwing {

	Sprite::Sprite(int x, int y, int w, int h) : rect{ x,y,w,h }
	{
	}

	void Sprite::setWH(int w, int h) {
		rect.w = w;
		rect.h = h;
	}

	void Sprite::setXY(int x, int y) {
		rect.x = x;
		rect.y = y;
	}

} //cwing