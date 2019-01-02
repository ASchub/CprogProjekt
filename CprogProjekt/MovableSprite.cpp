#include "MovableSprite.h"
#include "System.h"
#include <iostream>

using namespace std;

namespace cwing {
	int speed = BASE_SPEED; //max movement per tick, magic number
	bool movedThisTick = false; //resets every tick
	int xVel = 0;
	int yVel = 0;

	MovableSprite* MovableSprite::getInstance(int x, int y, const char path[]) {
		return new MovableSprite(x, y, path);
	}

	MovableSprite::MovableSprite(int x, int y, const char path[]) : Sprite(x, y, 0, 0, path)
	{
	}

	void MovableSprite::keyDown(const SDL_Event& event)
	{
		//cout << "inside keyDown for movablesprite" << endl;
		switch (event.key.keysym.sym) {
			//case SDLK_UP: cout << "keyup" << endl;
		case SDLK_UP:
			if (!movedThisTick) {
				yVel--;
				move();
				movedThisTick = true;
			} //move if max movement is not already reached
			break;
		case SDLK_DOWN:
			if (!movedThisTick) {
				yVel++;
				move();
				movedThisTick = true;
			}//move if max movement is not already reached
			break;
		case SDLK_RIGHT:
			if (!movedThisTick) {
				xVel++;
				move();
				movedThisTick = true;
			}//move if max movement is not already reached
			break;
		case SDLK_LEFT:
			if (!movedThisTick) {
				xVel--;
				move();
				movedThisTick = true;
			}//move if max movement is not already reached
			break;
		} //switch
	}

	void MovableSprite::move() {
		if(yVel > 0)
			setXY(getRect().x, getRect().y + speed);
		else if(yVel < 0)
			setXY(getRect().x, getRect().y - speed);
		else if(xVel > 0)
			setXY(getRect().x + speed, getRect().y);
		else if(xVel < 0)
			setXY(getRect().x - speed, getRect().y);

	}

	void MovableSprite::resetMoveThisTick() {
		movedThisTick = false;
		yVel = 0;
		xVel = 0;
	}

	void MovableSprite::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &getRect());
	}

	void MovableSprite::handleCollision(const Sprite* other) {
		setXY(300, 100);

		/*
		int BounceRate = speed * 3;
		int left, leftO;
		int right, rightO;
		int top, topO;
		int bottom, bottomO;

		//Calculate the sides of this
		left = getRect().x;
		right = getRect().x + getRect().w;
		top = getRect().y;
		bottom = getRect().y + getRect().h;

		//Calculate the sides of rect B
		leftO = other->getRect().x;
		rightO = other->getRect().x + other->getRect().w;
		topO = other->getRect().y;
		bottomO = other->getRect().y + other->getRect().h;

		//bounce off objekt.

		//If any of the sides from A are outside of B
		if (bottom <= topO) {
			cout << "something happened" << endl;
			setXY(getRect().x, getRect().y - BounceRate);
		}
		if (top >= bottomO) {
			cout << "something happened" << endl;
			setXY(getRect().x, getRect().y + BounceRate);
		}
		if (right <= leftO) {
			cout << "something happened" << endl;
			setXY(getRect().x - BounceRate, getRect().y);
		}
		if (left >= rightO) {
			cout << "something happened" << endl;
			setXY(getRect().x + BounceRate, getRect().y);
		}

		//If none of the sides from A are outside B
		*/

	}


} //cwing