#pragma once
#include <SDL.h>
#include "Sprite.h"

#include <string>
#include <memory>
#include <vector>
/*
See "Sprite.h" for information about general variables and functions.
*/
namespace cwing {
	class AnimatedSprite : public Sprite 
	{
	public:
		static shared_ptr<AnimatedSprite> getInstance(int x, int y, int w, int h, int nrOfFrames, const char path[]);
		~AnimatedSprite();

	protected:
		/*
		Constructor:
		The animation is done through a sprite sheet, the next frame is the one to the right of the current frame, loops until it reaches the last frame.
		Height, Width : defines how large the sprite should be, and how far between each frame in the spritesheet.
		*/
		AnimatedSprite(int x, int y, int w, int h, int nrOfFrames, const char path[]);
		void makeTexture(const char path[]);
		void draw() const;
		/*
		setDelay:
		Makes it possible to decide after how many ticks the picture should update.
		Changes the private int "delay".
		*/
		void setDelay(int d);
	private:
		int frames;
		int delay = 40;
		unique_ptr<SDL_Rect> srcrect;
	}; //class

} //cwing