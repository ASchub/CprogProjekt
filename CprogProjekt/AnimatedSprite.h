#pragma once
#include <SDL.h>
#include "Sprite.h"

#include <string>
#include <memory>
#include <vector>

namespace cwing {
	class AnimatedSprite : public Sprite 
	{
	public:
		static shared_ptr<AnimatedSprite> getInstance(int x, int y, int w, int h, int nrOfFrames, const char path[]);
		~AnimatedSprite();

	protected:
		AnimatedSprite(int x, int y, int w, int h, int nrOfFrames, const char path[]);
		void makeTexture(const char path[]);
		void draw() const;
		void setDelay(int d);
	private:
	}; //class

} //cwing