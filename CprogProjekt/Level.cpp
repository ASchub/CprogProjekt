#include "Level.h"
#include <SDL.h>
#include "System.h"
#include "Sprite.h"
#include "GameEngine.h"

#include <iostream>
#include <memory>



namespace cwing {

	Level::~Level() {
		while (!sprites.empty()) {
			sprites.pop_back();
		}
		while (!added.empty()) {
			added.pop_back();
		}
		while (!removed.empty()) {
			removed.pop_back();
		}
	}	//Destruktor

	shared_ptr<Level> Level::getInstance(bool gravity, int downwardsMotion) {
		return shared_ptr<Level>(new Level(gravity, downwardsMotion));
	}
	shared_ptr<Level> Level::getInstance() {
		return shared_ptr<Level>(new Level(false, 0));
	}

	Level::Level(bool gravityOn, int downwardsMotion) {
		gravity = gravityOn;
		gravityStrength = downwardsMotion;
	}//Konstruktor

	void Level::add(shared_ptr<Sprite> s) {
		added.push_back(s);
	}

	void Level::remove(shared_ptr<Sprite> s) {
		removed.push_back(s);
	}

	void Level::setGravity(bool g, int downwardsmotion) {
		gravity = g;
		gravityStrength = downwardsmotion;
	}

	void Level::tick() {
		collisionDetection();
		npcEvents();
		prepareNextTick();
	}

	void Level::runGravity() {
		for (shared_ptr<Sprite> s : sprites) {
			if (s->isAffectedByGravity()) {
				s->fall(gravityStrength);
			}
		}
	}

	void Level::collisionDetection() {
		for (shared_ptr<Sprite> a : sprites) {
			for (shared_ptr<Sprite> b : sprites) {
				if (a != b) {
					if (checkCollision(a, b)) {
						a->handleCollision(b);
						b->handleCollision(a);
					}
				}
			}
		}
	}

	bool Level::checkCollision(shared_ptr<Sprite> a, shared_ptr<Sprite> b) {
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;
		shared_ptr<SDL_Rect> aRect = a->getRect();
		shared_ptr<SDL_Rect> bRect = b->getRect();

		//Calculate the sides of rect A
		leftA = aRect->x;
		rightA = aRect->x + aRect->w;
		topA = aRect->y;
		bottomA = aRect->y + aRect->h;

		//Calculate the sides of rect B
		leftB = bRect->x;
		rightB = bRect->x + bRect->w;
		topB = bRect->y;
		bottomB = bRect->y + bRect->h;

		//If any of the sides from A are outside of B
		if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB))
			return false;
		//If none of the sides from A are outside B
		return true;
	}

	void Level::npcEvents() {

	}

	void Level::prepareNextTick() {

		//tar bort alla sprites som f�rsvunnit under h�ndelsef�rloppen., detta g�rs i slutet av loopen efter alla h�ndelser har hanterats.
		for (shared_ptr<Sprite> s : removed) {
			for (auto it = sprites.begin(); it != sprites.end();) //auto i �r en iterator �ver vectorn.
				if (*it == s) {
					it = sprites.erase(it); //erase returnerar en iterator till n�sta element, s� vi kan hoppa �ver det vi tar bort.
				}
				else
					it++; //f�r bara flytta fram iteratorn om vi inte tar bort ett element, eftersom vi redan f�r pekaren till n�sta via erase.
		}

		while (!removed.empty()) {
			removed.pop_back();
		}

		for (shared_ptr<Sprite> s : sprites) {
			s->resetMoveThisTick();
		} //resets movement as prep for next tick,efter removed pga on�digt att reset:a objekt som tas bort

		//L�gger till saker som tillkommit under h�ndelsef�rloppet
		for (shared_ptr<Sprite> s : added) {
			sprites.push_back(s);
		}
		while (!added.empty()) {
			added.pop_back();
		}

		//nu g�r vi igenom alla komponenter och ritar ut dem
		for (shared_ptr<Sprite> s : sprites)
			s->draw();

		//k�r gravitation inf�r n�sta tick, f�rutsatt att gravitationen �r p�
		if (gravity) {
			runGravity();
		}
	}

	} //cwing