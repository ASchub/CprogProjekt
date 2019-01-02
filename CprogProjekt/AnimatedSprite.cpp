#include "AnimatedSprite.h"
#include "System.h"
#include <iostream>
#include "Sprite.h"
using namespace std;

namespace cwing {
	int nrOfFrames = 7;
	int currentFrame = 0;
	int delay = 0;
	SDL_Rect srcrect;

	AnimatedSprite* AnimatedSprite::getInstance(int x, int y, const char path[]) {
		return new AnimatedSprite(x, y, path);
	}

	AnimatedSprite::AnimatedSprite(int x, int y, const char path[]) : Sprite(x, y, 0, 0, path)
	{
		setWH(14, 20);
		srcrect = { 0,0,14,20 };
		/*loadImageIntoFrames();
		cout << "AnimatedSpriteConstructor" << endl;*/
	}

	/*void AnimatedSprite::loadImageIntoFrames() {
		for (int i = 0; i < nrOfFrames; i++) {
			SDL_Rect rect = { i * 14,0,14,20 };
			frames[i] = &rect;
			cout << "Loaded into frame" << endl;
		}
	}*/

	void AnimatedSprite::draw() const {
			if (currentFrame >= nrOfFrames) {
				currentFrame = 0;
			}
			srcrect.x = (currentFrame * 14);
			SDL_RenderCopy(sys.getRen(), getTexture(), &srcrect, &getRect());

			if (delay > 1000) {
				currentFrame++;
				delay = 0;
			}
			delay++;
	}


} //cwing