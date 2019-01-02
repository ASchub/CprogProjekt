#include "MovableSprite.h"
#include "System.h"
#include <iostream>

using namespace std;

namespace cwing {
	int speed = 5; //max movement per tick, magic number
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

	void MovableSprite::handleCollision() {
		cout << "Movable Sprite collided" << endl;
	}

} //cwing