#include "AnimatedSprite.h"
#include "System.h"
#include "Sprite.h"

#include <iostream>
#include <memory>
using namespace std;

namespace cwing {

	int currentFrame;
	int delayCounter;

	shared_ptr<AnimatedSprite> AnimatedSprite::getInstance(int x, int y, int w, int h, int nrOfFrames, const char path[]) {
		return shared_ptr<AnimatedSprite>(new AnimatedSprite(x, y, w, h, nrOfFrames, path));
	}
	
	AnimatedSprite::~AnimatedSprite() {
	}

	AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, int nrOfFrames, const char path[]) : Sprite(x, y, w, h, path)
	{
		currentFrame = 0;
		delayCounter = 0;

		setSolid(false);
		frames = nrOfFrames;
		setWH(w, h);
		srcrect = make_unique<SDL_Rect>();
		srcrect->x = 0;
		srcrect->y = 0;
		srcrect->w = w;
		srcrect->h = h;
	}

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
	} 

	void AnimatedSprite::draw() const {
			if (currentFrame >= frames) {
				currentFrame = 0;
			}
			srcrect->x = (currentFrame * 14);
			SDL_RenderCopy(sys.getRen(), getTexture(), srcrect.get(), getRect().get());

			if (delayCounter > delay) {
				currentFrame++;
				delayCounter = 0;
			}
			delayCounter++;
	}


} //cwing