#include "Sprite.h"
#include "System.h"

#include <memory>

using namespace std;

namespace cwing {

	Sprite::Sprite(int x, int y, int w, int h, const char path[])
	{
		rect = shared_ptr<SDL_Rect>(new SDL_Rect());
		rect->x = x;
		rect->y = y;
		rect->w = w;
		rect->h = h;
		makeTexture(path);
	}

	void Sprite::setWH(int w, int h) {
		rect->w = w;
		rect->h = h;
	}

	void Sprite::fall(int pixels) {
		rect->y += pixels;
	}

	void Sprite::makeTexture(const char path[]) {
		if (texture != nullptr)
			SDL_DestroyTexture(texture);

		SDL_Surface* surf = SDL_LoadBMP(path);
		texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
		setWH(surf->w, surf->h);
		SDL_FreeSurface(surf);
	}

	void Sprite::setXY(int x, int y) {
		rect->x = x;
		rect->y = y;
	}

} //cwing