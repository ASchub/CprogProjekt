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
		//virtual void handleCollision(shared_ptr<const Sprite> other)
		void draw() const;
		void handleCollision(std::shared_ptr<SDL_Rect> intersection);
		//void keyDown(const SDL_Event& event);
		void resetMoveThisTick();
		void moveUp();
		void moveDown();
		void moveRight();
		void moveLeft();
		void jump();
	protected:
		MovableSprite(int x, int y, const char path[]);
		//virtual void handleCollision(shared_ptr<const Sprite> other);
	private:
		int xVel = 0;
		int yVel = 0;
		bool bouncing;
	};

} //cwing