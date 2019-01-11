#include "MovableSprite.h"
#include "System.h"

#include <iostream>
#include <memory>

using namespace std;

namespace cwing {
	int speed = spriteSpeed; //max movement per tick, magic number
	bool movedThisTick = false; //resets every tick

	shared_ptr<MovableSprite> MovableSprite::getInstance(int x, int y, const char path[]) {
		return shared_ptr<MovableSprite>(new MovableSprite(x, y, path));
	}

	MovableSprite::MovableSprite(int x, int y, const char path[]) : Sprite(x, y, 0, 0, path)
	{
	}

	void MovableSprite::moveUp() {
		yVel -= speed;
		setXY(getRect()->x, getRect()->y - speed);
	}

	void MovableSprite::moveDown() {
		yVel += speed;
		setXY(getRect()->x, getRect()->y + speed);
	}

	void MovableSprite::moveRight() {
		xVel += speed;
		setXY(getRect()->x + speed, getRect()->y);
	}

	void MovableSprite::moveLeft() {
		xVel -= speed;
		setXY(getRect()->x - speed, getRect()->y);
	}

	void MovableSprite::resetMoveThisTick() {
		movedThisTick = false;
		yVel = 0;
		xVel = 0;
	}

	void MovableSprite::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, getRect().get());

	}

	void MovableSprite::handleCollision(std::shared_ptr<SDL_Rect> intersection) {
		int move = speed;
		if (bounces > 0) {
			move = speed * (1 + bounceRate);
		}
		if (yVel > 0)
			setXY(getRect()->x, getRect()->y - move);
		else if (yVel < 0)
			setXY(getRect()->x, getRect()->y + move);
		else if (xVel > 0)
			setXY(getRect()->x - move, getRect()->y);
		else if (xVel < 0)
			setXY(getRect()->x + move, getRect()->y);

		resetMoveThisTick();
	}


	/*void MovableSprite::handleCollision(shared_ptr<const Sprite> other) {
		int move = speed;
		if (bounces > 0) {
			move = speed*(1+ bounceRate);
		}
		if (yVel > 0)
			setXY(getRect()->x, getRect()->y - move);
		else if (yVel < 0)
			setXY(getRect()->x, getRect()->y + move);
		else if (xVel > 0)
			setXY(getRect()->x - move, getRect()->y);
		else if (xVel < 0)
			setXY(getRect()->x + move, getRect()->y);

		resetMoveThisTick();
	}*/

	//void MovableSprite::handleCollision(shared_ptr<const Sprite> other) {
	//	setXY(300, 100);
	//}


} //cwing