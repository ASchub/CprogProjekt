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

	void Sprite::checkCollideWithWindow() {
		int left, right, top, bottom;
		int winLeft, winRight, winTop, winBottom;

		left = rect->x;
		right = rect->x + rect->w;
		top = rect->y;
		bottom = rect->y + rect->h;

		winLeft = 0;
		winRight = SDL_GetWindowSurface(sys.getWin())->w;
		winTop = 0;
		winBottom = SDL_GetWindowSurface(sys.getWin())->h;
		if (left <= winLeft) {
			rect->x = 0;
		}
		if (right >= winRight) {
			rect->x = winRight - rect->w;
		}
		if (top <= winTop) {
			rect->y = 0;
		}
		if (bottom >= winBottom) {
			rect->y = winBottom - rect->h;
		}
	}

	bool Sprite::checkCollision(std::shared_ptr<const Sprite> other) {
		//The sides of the rectangles
		int left, leftO;
		int right, rightO;
		int top, topO;
		int bottom, bottomO;
		shared_ptr<SDL_Rect> rect = getRect();
		shared_ptr<SDL_Rect> oRect = other->getRect();

		//Calculate the sides of rect A
		left = rect->x;
		right = rect->x + rect->w;
		top = rect->y;
		bottom = rect->y + rect->h;

		//Calculate the sides of rect B
		leftO = oRect->x;
		rightO = oRect->x + oRect->w;
		topO = oRect->y;
		bottomO = oRect->y + oRect->h;

		//If any of the sides from A are outside of B
		if (bottom <= topO) {
			return false;
		}
		if (top >= bottomO) {
			return false;
		}
		if (right <= leftO) {
			return false;
		}
		if (left >= rightO) {
			return false;
		}

		handleCollision(other);
		return true;
	}

} //cwing