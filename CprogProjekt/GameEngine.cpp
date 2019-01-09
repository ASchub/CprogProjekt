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
	Vectorerna försvinner automatiskt, men vi måste gå igenom vectorn och radera allt innehåll
	added, removed bör alltid vara tomma om avstängning kallats, men ifall något gick fel mitt i går vi även igenom dem...
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
		bool quit = false; //styr när huvudloopen ska avbrytas.

		while (!quit) {
			now = SDL_GetTicks();

			if (nextTick <= now) {
				quit = handleEvents(); //also handles hotkeys now, helpfunction "checkHotkeys()"
				if (quit)
					break;
				SDL_RenderClear(sys.getRen()); //Behöver först rensa allt gammalt om man ska rita på nytt
				levels.at(currentLevel)->tick(); //kör tick-metod inuti leveln, inklusive ritar ut objekt
				SDL_RenderPresent(sys.getRen());
				nextTick += (1000 / maxFps);
			} //kör denna kod om vi kommit fram till nästa tick
			else {
				SDL_Delay(nextTick - now);
			} //vänta tills nästa tick
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
			//lång switchsats som kollar eventhändelser.
			switch (event.type) {
			case SDL_QUIT: return true;
			default: {
				checkHotkeys(event);
				break;
			}
			} //switch
		} //inre while (spelar händelser)
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