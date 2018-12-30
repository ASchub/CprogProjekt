#include "TestSprite.h"
#include "System.h"

using namespace std;

namespace cwing {

	TestSprite* TestSprite::getInstance(int x, int y, const char path[]) {
		return new TestSprite(x, y, path);
	}

	TestSprite::TestSprite(int x, int y, const char path[]) : Sprite(x, y, 0, 0)
	{
		makeTexture(path);
	}

	void TestSprite::makeTexture(const char path[]) {
		if (texture != nullptr)
			SDL_DestroyTexture(texture);

		SDL_Surface* surf = SDL_LoadBMP(path);
		texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
		setWH(surf->w, surf->h);
		SDL_FreeSurface(surf);
	}

	void TestSprite::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &getRect());
	}


	TestSprite::~TestSprite()
	{
		SDL_DestroyTexture(texture);
	}

}