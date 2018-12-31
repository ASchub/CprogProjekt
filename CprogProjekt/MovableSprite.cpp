#include "MovableSprite.h"
#include "System.h"
#include <iostream>

using namespace std;

namespace cwing {

	MovableSprite* MovableSprite::getInstance(int x, int y, const char path[]) {
		return new MovableSprite(x, y, path);
	}

	MovableSprite::MovableSprite(int x, int y, const char path[]) : Sprite(x, y, 0, 0, path)
	{
	}

	void MovableSprite::keyDown(const SDL_Event& event)
	{	
		cout << "inside keyDown for movablesprite" << endl;
		switch (event.key.keysym.sym) {
		//case SDLK_UP: cout << "keyup" << endl;
		case SDLK_UP: setXY(getRect().x, getRect().y - 1); cout << "UP" << endl; break;
		case SDLK_DOWN: setXY(getRect().x, getRect().y + 1); cout << "DOWN" << endl; break;
		case SDLK_RIGHT: setXY(getRect().x + 1, getRect().y); cout << "RIGHT" << endl; break;
		case SDLK_LEFT: setXY(getRect().x - 1, getRect().y); cout << "LEFT" << endl; break;
		}

	}

	void MovableSprite::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &getRect());
	}

} //cwing