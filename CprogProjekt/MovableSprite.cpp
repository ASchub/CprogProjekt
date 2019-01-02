#include "MovableSprite.h"
#include "System.h"
#include <iostream>

using namespace std;

namespace cwing {
	int speed = BASE_SPEED; //max movement per tick, magic number
	int movedThisTick = 0; //resets every tick

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
			if (movedThisTick < speed) {
				setXY(getRect().x, getRect().y - 1); cout << "UP" << endl;
				movedThisTick++;
			} //move if max movement is not already reached
			break;
		case SDLK_DOWN:
			if (movedThisTick < speed) {
				setXY(getRect().x, getRect().y + 1); cout << "DOWN" << endl;
				movedThisTick++;
			}//move if max movement is not already reached
			break;
		case SDLK_RIGHT:
			if (movedThisTick < speed) {
				setXY(getRect().x + 1, getRect().y); cout << "RIGHT" << endl;
				movedThisTick++;
			}//move if max movement is not already reached
			break;
		case SDLK_LEFT:
			if (movedThisTick < speed) {
				setXY(getRect().x - 1, getRect().y); cout << "LEFT" << endl;
				movedThisTick++;
			}//move if max movement is not already reached
			break;
		}

	}

	void MovableSprite::resetMoveThisTick() {
		movedThisTick = 0;
	}

	void MovableSprite::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &getRect());
	}

	void MovableSprite::handleCollision(const Sprite* other) {
		Uint32 BounceRate = BASE_SPEED * 3;
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

	}


} //cwing