#pragma once
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include <string>

namespace cwing {
	class AnimatedSprite : public Sprite 
	{
	public:
		static AnimatedSprite* getInstance(int x, int y, const char path[]);

	protected:
		AnimatedSprite(int x, int y, const char path[]);
		void draw() const;
	private:
	}; //class

} //cwing