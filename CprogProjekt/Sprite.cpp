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

	int Sprite::tick(std::vector<shared_ptr<Sprite>> sprites, std::shared_ptr<SDL_Rect> gameArea, bool gameIsPaused) {
		if (!gameIsPaused) {
			automaticBehaviour();
			checkBoundaryCollision(gameArea);
		}
			for (shared_ptr<Sprite> s : sprites) {
				if (this != s.get()) {
					checkSpriteCollision(s);
				}
			}
		draw();
		return 0;
	}

	bool Sprite::checkSpriteCollision(shared_ptr<Sprite> other) {
		shared_ptr<SDL_Rect> intersectionResult = shared_ptr<SDL_Rect>(new SDL_Rect());
		if (checkRectCollision(other->getRect(), intersectionResult) && isSolid() && other->isSolid()) {
				handleCollision(intersectionResult);
				other->handleCollision(intersectionResult);
				return true;
		}
		return false;
	}
	
	bool Sprite::checkBoundaryCollision(shared_ptr<SDL_Rect> playableArea) {
		shared_ptr<SDL_Rect> intersectionResult = shared_ptr<SDL_Rect>(new SDL_Rect());
		checkRectCollision(playableArea, intersectionResult);
		if(intersectionResult->w != getRect()->w || intersectionResult->h != getRect()->h) {
			adjustInsideWindow(intersectionResult);
			return true;
		}
		return false;
	}

	void Sprite::adjustInsideWindow(shared_ptr<SDL_Rect> intersectionResult) {
		int xDiff = getRect()->x - intersectionResult->x;
		int yDiff = getRect()->y - intersectionResult->y;
		int wDiff = getRect()->w - intersectionResult->w;
		int hDiff = getRect()->h - intersectionResult->h;
		if (wDiff != 0) { //om någon del av spriten är utanför areans x-axel
			if (xDiff >= 0) { //om spriten krockar med högra kanten
				getRect()->x -= wDiff; //justera x-position med så mycket som spriten är utanför frame
			} else{ //spriten krockar med vänstra kanten
				getRect()->x += wDiff;
			}
		}
		if (hDiff != 0) { //om någon del av spriten är utanför areans y-axel
			if (yDiff >= 0) { //om spriten krockar med nedre kanten
				getRect()->y -= hDiff; // justera y-position med så mycket som spriten är utanför frame
			} else { //spriten krockar med övre kanten
				getRect()->y = intersectionResult->y; //sätt y-position till kanten
			}
		}
	}

	bool Sprite::checkRectCollision(shared_ptr<SDL_Rect> otherRect, shared_ptr<SDL_Rect> intersectionResult) {
		if (SDL_IntersectRect(getRect().get(), otherRect.get(), intersectionResult.get())) {
			return true;
		}
		return false;
	}

} //cwing