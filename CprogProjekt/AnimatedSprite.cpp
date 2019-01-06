#include "AnimatedSprite.h"
#include "System.h"
#include <iostream>
#include "Sprite.h"
#include <memory>
using namespace std;

namespace cwing {
	int frames;
	int currentFrame = 0;
	int delay = 40;
	int delayCounter = 0;
	unique_ptr<SDL_Rect> srcrect;

	AnimatedSprite* AnimatedSprite::getInstance(int x, int y, int w, int h, int nrOfFrames, const char path[]) {
		return new AnimatedSprite(x, y, w, h, nrOfFrames, path);
	}
	
	AnimatedSprite::~AnimatedSprite() {
	}

	AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, int nrOfFrames, const char path[]) : Sprite(x, y, w, h, path)
	{
		frames = nrOfFrames;
		setWH(w, h);
		srcrect = make_unique<SDL_Rect>();
		srcrect->x = 0;
		srcrect->y = 0;
		srcrect->w = w;
		srcrect->h = h;
	} //Animationen görs genom ett sprite sheet, nästa frame hämtas till höger om nuvarande frame (och loopar om man kommit till sista framen)
	//Height/Width definierar hur stor spriten skall vara, och därmed också hur långt det är mellan olika frames på sprite sheetet.

	void AnimatedSprite::makeTexture(const char path[]) {
		if (getTexture() != nullptr)
			SDL_DestroyTexture(getTexture());

		SDL_Surface* surf = SDL_LoadBMP(path);
		SDL_Texture* tempTexture = getTexture();
		tempTexture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
		SDL_FreeSurface(surf);
	}

	void AnimatedSprite::setDelay(int d) {
		delay = d;
	} //Möjliggör att själv avgöra efter hur många ticks bilden skall uppdateras

	void AnimatedSprite::draw() const {
			if (currentFrame >= frames) {
				currentFrame = 0;
			}
			srcrect->x = (currentFrame * 14);
			SDL_RenderCopy(sys.getRen(), getTexture(), srcrect.get(), getRect());

			if (delayCounter > delay) {
				currentFrame++;
				delayCounter = 0;
			}
			delayCounter++;
	}


} //cwing