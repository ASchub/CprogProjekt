#pragma once
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include <string>

namespace cwing {
	class AnimatedSprite : public Sprite 
	{
	public:
		static AnimatedSprite* getInstance(int x, int y, int w, int h, int nrOfFrames, const char path[]);
		~AnimatedSprite();

	protected:
		AnimatedSprite(int x, int y, int w, int h, int nrOfFrames, const char path[]);
		void makeTexture(const char path[]);
		void draw() const;
		void setDelay(int d);
	private:
	}; //class

} //cwing