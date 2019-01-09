#include "GameEngine.h"
#include <SDL.h>
#include "System.h"
#include "Sprite.h"
#include "MovableSprite.h"
#include "StationarySprite.h"
#include "AnimatedSprite.h"

#include <iostream>
#include <memory>



namespace cwing {



	GameEngine::GameEngine(int max_Fps, int min_Fps)
	{
		maxFps = max_Fps;
		minFps = min_Fps;
	}

	/*
	Vectorerna f�rsvinner automatiskt, men vi m�ste g� igenom vectorn och radera allt inneh�ll
	added, removed b�r alltid vara tomma om avst�ngning kallats, men ifall n�got gick fel mitt i g�r vi �ven igenom dem...
	*/
	GameEngine::~GameEngine() 
	{
		while (!sprites.empty()) {
			sprites.pop_back();
		}
		while (!added.empty()) {
			added.pop_back();
		}
		while (!removed.empty()) {
			removed.pop_back();
		}
	}

	void GameEngine::add(shared_ptr<Sprite> s) {
		cout << "sprite" << endl;
		added.push_back(s);
	}

	void GameEngine::add(shared_ptr<Hotkey> h) {
		cout << "hotkey" << endl;
		hotkeys.push_back(h);
	}

	void GameEngine::add(shared_ptr<Level> l) {
		cout << "level" << endl;
		levels.push_back(l);
	}

	void GameEngine::addPlayer(shared_ptr<Sprite> p) {
		player = p;
	}

	void GameEngine::remove(shared_ptr<Sprite> s) {
		removed.push_back(s);
	}

	void GameEngine::setMaxFps(int i) {
		maxFps = i;
	}

	void GameEngine::setMinFps(int i) {
		minFps = i;
	}

	void GameEngine::run() {
		SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
		bool quit = false; //styr n�r huvudloopen ska avbrytas.

		while (!quit) {
			now = SDL_GetTicks();

			if (nextTick <= now) {
				quit = handleEvents(); //also handles hotkeys now, helpfunction "checkHotkeys()"
				if (quit)
					break;
				SDL_RenderClear(sys.getRen()); //Beh�ver f�rst rensa allt gammalt om man ska rita p� nytt
				levels.at(currentLevel)->tick(); //k�r tick-metod inuti leveln, inklusive ritar ut objekt
				SDL_RenderPresent(sys.getRen());
				nextTick += (1000 / maxFps);
			} //k�r denna kod om vi kommit fram till n�sta tick
			else {
				SDL_Delay(nextTick - now);
			} //v�nta tills n�sta tick
		} //yttre while

	} //run

	void GameEngine::checkHotkeys(SDL_Event &event) {
		for (shared_ptr<Hotkey> h : hotkeys) {
			if (event.key.keysym.sym == h->getKey()) {
				h->perform();
			}
		}
	}

	bool GameEngine::handleEvents() { //returns TRUE if quit should be true
		while (SDL_PollEvent(&event)) {
			//l�ng switchsats som kollar eventh�ndelser.
			switch (event.type) {
			case SDL_QUIT: return true;
			default: {
				checkHotkeys(event);
				break;
			}
			} //switch
		} //inre while (spelar h�ndelser)
		return false;
	}

	void GameEngine::nextLevel() {
		currentLevel++;
		if (levels.at(currentLevel) != nullptr) {
			buildLevel(levels.at(currentLevel));
		}
	}

	void GameEngine::buildLevel(shared_ptr<Level> l) {

	}
} //cwing