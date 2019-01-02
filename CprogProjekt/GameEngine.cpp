#include "GameEngine.h"
#include <SDL.h>
#include "System.h"
#include <iostream>

namespace cwing {

 // initiellt värde, magiskt nummer
	Uint32 nextTick = SDL_GetTicks(); //initiellt värde, uppdateras varje tick //TODO - ska vara en pointer?
	Uint32 now;
	SDL_Event* event = nullptr;

	GameEngine::GameEngine()
	{
		maxFps = 70;
		minFps = 5;
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

	void GameEngine::add(Sprite* s) {
		added.push_back(s);
	}

	void GameEngine::remove(Sprite *s) {
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
				//cout << "loop BEGIN" << endl;

				quit = handleEvents();
				if (quit)
					break;

				npcEvents();

				//collisionDetection();

				/*
				Här borde andra händelser ske, som att fiender rör sig m.m.
				Detta markerar slutet på interaktioner, efter detta tar vi bort och lägger till saker samt ritar om och förbereder för nästa tick.
				Gör inga händelsehanteringar efter denna punkt!
				*/


				prepareNextTick();

			} //kör denna kod om vi kommit fram till nästa tick
			else {
				SDL_Delay(nextTick - now);
			} //vänta tills nästa tick
		} //yttre while

	} //run

	void GameEngine::collisionDetection() {
		for (Sprite* a : sprites) {
			for (Sprite* b : sprites) {
				if (a != b) {
					if (checkCollision(a, b)) {
						//a->handleCollision(b);
						//b->handleCollision(a);
					}
				}
			}
		}
	}

	bool GameEngine::checkCollision(Sprite* a, Sprite* b) { //returns true if objects collided.
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a->getRect().x;
		rightA = a->getRect().x + a->getRect().w;
		topA = a->getRect().y;
		bottomA = a->getRect().y + a->getRect().h;

		//Calculate the sides of rect B
		leftB = b->getRect().x;
		rightB = b->getRect().x + b->getRect().w;
		topB = b->getRect().y;
		bottomB = b->getRect().y + b->getRect().h;

		//If any of the sides from A are outside of B
		if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB))
			return false;
		//If none of the sides from A are outside B
		return true;
	}

	void GameEngine::npcEvents() {

	}

	void GameEngine::prepareNextTick() {

		//tar bort alla sprites som försvunnit under händelseförloppen., detta görs i slutet av loopen efter alla händelser har hanterats.
		for (Sprite* s : removed) {
			for (auto it = sprites.begin(); it != sprites.end();) //auto i är en iterator över vectorn.
				if (*it == s) {
					it = sprites.erase(it); //erase returnerar en iterator till nästa element, så vi kan hoppa över det vi tar bort.
					delete s;
				}
				else
					it++; //får bara flytta fram iteratorn om vi inte tar bort ett element, eftersom vi redan får pekaren till nästa via erase.
		}

		for (Sprite* s : sprites) {
			s->resetMoveThisTick();
		} //resets movement as prep for next tick,efter removed pga onödigt att reset:a objekt som tas bort

		removed.clear(); //nu när vi tagit bort allt rensar vi removed så vi kan använda på nytt i nästa ticks.

		//Lägger till saker som tillkommit under händelseförloppet
		for (Sprite* s : added) {
			sprites.push_back(s);
		}

		//behöver rita alla komponenter, ifall något event ändrar på någon grafik.
		SDL_RenderClear(sys.getRen()); //Behöver först rensa allt gammalt om man ska rita på nytt
		//nu går vi igenom alla komponenter och ritar ut dem
		//cout << "END loop, DRAW" << endl;
		for (Sprite* s : sprites)
			s->draw();
		SDL_RenderPresent(sys.getRen());

		nextTick += (1000 / maxFps);
	}

	bool GameEngine::handleEvents() { //returns TRUE if quit should be true
		while (SDL_PollEvent(&event)) {
			//lång switchsats som kollar eventhändelser.
			switch (event.type) {
			case SDL_QUIT: return true;
			case SDL_MOUSEBUTTONDOWN:
				for (Sprite* s : sprites) //kan va auto
					s->mouseDown(event); //funk i component som kollar om eventet är till sig.
			case SDL_MOUSEBUTTONUP:
				for (Sprite* s : sprites)
					s->mouseUp(event);
			case SDL_KEYDOWN: {
				for (Sprite* s : sprites)
					s->keyDown(event);
				break;
			}
			case SDL_KEYUP:
				for (Sprite* s : sprites)
					s->keyUp(event);

			} //switch

		} //inre while (spelar händelser)
		return false;
	}

} //cwing