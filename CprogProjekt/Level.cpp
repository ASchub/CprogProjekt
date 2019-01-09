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
		for (shared_ptr<Sprite> s : sprites) {
			s->tick(sprites);
		}
		prepareNextTick();
	}

	void Level::runGravity() {
		for (shared_ptr<Sprite> s : sprites) {
			if (s->isAffectedByGravity()) {
				s->fall(gravityStrength);
			}
		}
	}

	void Level::prepareNextTick() {

		//tar bort alla sprites som försvunnit under händelseförloppen., detta görs i slutet av loopen efter alla händelser har hanterats.
		for (shared_ptr<Sprite> s : removed) {
			for (auto it = sprites.begin(); it != sprites.end();) //auto i är en iterator över vectorn.
				if (*it == s) {
					it = sprites.erase(it); //erase returnerar en iterator till nästa element, så vi kan hoppa över det vi tar bort.
				}
				else
					it++; //får bara flytta fram iteratorn om vi inte tar bort ett element, eftersom vi redan får pekaren till nästa via erase.
		}

		while (!removed.empty()) {
			removed.pop_back();
		}

		for (shared_ptr<Sprite> s : sprites) {
			s->resetMoveThisTick();
		} //resets movement as prep for next tick,efter removed pga onödigt att reset:a objekt som tas bort

		//Lägger till saker som tillkommit under händelseförloppet
		for (shared_ptr<Sprite> s : added) {
			sprites.push_back(s);
		}
		while (!added.empty()) {
			added.pop_back();
		}

		//kör gravitation inför nästa tick, förutsatt att gravitationen är på
		if (gravity) {
			runGravity();
		}
	}

	} //cwing