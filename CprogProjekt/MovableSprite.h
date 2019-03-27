#pragma once
#include <SDL.h>
#include "Sprite.h"

#include <string>
#include <memory>
/*
See "Sprite.h" for information about general variables and functions.
*/
namespace cwing {

	class MovableSprite : public Sprite
	{
	public:
		static shared_ptr<MovableSprite> getInstance(int x, int y, const char path[]);
		void draw() const;

		/*
		When a movable sprite collides with something it stops at the edge of the other sprite, and cant progress.
		*/
		void handleCollision(std::shared_ptr<SDL_Rect> intersection);

		/*
		A MovableSprite can only move once per tick, this is called at the end of the sprites tick.
		*/
		void resetMoveThisTick();

		/*
		functions for moving the sprite easily.
		*/
		void moveUp();
		void moveDown();
		void moveRight();
		void moveLeft();
		void jump();

		/*
		getters and setters
		*/
		int getSpeed() { return speed; }
		void setSpeed(int s) { speed = s; }
	protected:
		MovableSprite(int x, int y, const char path[]);
	private:
		/*
		variables for the movement functions
		*/
		int speed = 10;
		bool movedThisTick = false;
		int xVel = 0;
		int yVel = 0;

		// A-grade things we did not have time to implement correctly {
		bool bouncing;
		// }
	};

} //cwing