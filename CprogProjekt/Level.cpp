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

	std::shared_ptr<Level> Level::getInstance(bool gravity, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea) {
		return std::shared_ptr<Level>(new Level(gravity, downwardsMotion, gameArea));
	}
	std::shared_ptr<Level> Level::getInstance() {
		std::shared_ptr<SDL_Rect> gameArea = std::shared_ptr<SDL_Rect>(new SDL_Rect());
		gameArea->w = 800; //TODO - fixa så w och h är anpassade efter fönsterstorlek.
		gameArea->h = 600;
		gameArea->x = 0;
		gameArea->y = 0;
		return std::shared_ptr<Level>(new Level(false, 0, gameArea));
	}

	Level::Level(bool gravityOn, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea) {
		gravity = gravityOn;
		gravityStrength = downwardsMotion;
		playableArea = gameArea;
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
			s->tick(sprites, playableArea);
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