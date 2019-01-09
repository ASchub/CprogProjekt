#pragma once
#include <SDL.h>
#include "Sprite.h"

#include <string>
#include <memory>

namespace cwing {

	class MovableSprite : public Sprite
	{
	public:
		static shared_ptr<MovableSprite> getInstance(int x, int y, const char path[]); //only supports BMP paths atm.
		void handleCollision(shared_ptr<const Sprite> other);
		void draw() const;
		void keyDown(const SDL_Event& event);
		void resetMoveThisTick();
		void move();
	protected:
		MovableSprite(int x, int y, const char path[]);
	private:
	};

} //cwing