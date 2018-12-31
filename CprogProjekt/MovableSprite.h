#pragma once
#include <SDL.h>
#include "Sprite.h"
#include <string>

namespace cwing {

	class MovableSprite : public Sprite
	{
	public:
		static MovableSprite* getInstance(int x, int y, const char path[]); //only supports BMP paths atm.
		void draw() const;
		void keyDown(const SDL_Event& event);
	protected:
		MovableSprite(int x, int y, const char path[]);
	private:

	};

} //cwing