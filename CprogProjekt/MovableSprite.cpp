#include "MovableSprite.h"
#include "System.h"

#include <iostream>
#include <memory>

using namespace std;

namespace cwing {
	//int speed = spriteSpeed; //max movement per tick, magic number
	 //resets every tick

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

	void MovableSprite::jump() {
		cout << "jump" << endl;
		getRect()->y -= speed*5;
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
		if (intersection->w >= intersection->h) { //krock huvudsakligen vertikalt, eller lika mycket vertikalt som horisontellt
			if (getRect()->y == intersection->y) { //krockar med andra spritens nederkant
				getRect()->y += intersection->h;
			}
			else { // krock med andra spritens överkant
				getRect()->y -= intersection->h;
			}
		}
		else { // krock huvudsakligen horisontellt
			if (getRect()->x == intersection->x) { // krock med andra spritens högerkant
				getRect()->x += intersection->w;
			}
			else { //krock med andra spritens nederkant
				getRect()->x -= intersection->w;
			}
		}
	}

} //cwing