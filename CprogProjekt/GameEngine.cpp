#include "GameEngine.h"
#include <SDL.h>
#include "System.h"
#include "Sprite.h"
#include "MovableSprite.h"

#include <iostream>
#include <memory>



namespace cwing {

 // initiellt v�rde, magiskt nummer
	Uint32 nextTick = SDL_GetTicks(); //initiellt v�rde, uppdateras varje tick //TODO - ska vara en pointer?
	Uint32 now;

	GameEngine::GameEngine()
	{
		maxFps = 70;
		minFps = 5;
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
		s->handleCollision(s);
		added.push_back(s);
	}

	void GameEngine::add(shared_ptr<Hotkey> h) {
		hotkeys.push_back(h);
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
				//cout << "loop BEGIN" << endl;

				quit = handleEvents(); //also handles hotkeys now, helpfunction "checkHotkeys()"
				if (quit)
					break;

				npcEvents();

				collisionDetection(); //needs work

				/*
				H�r borde andra h�ndelser ske, som att fiender r�r sig m.m.
				Detta markerar slutet p� interaktioner, efter detta tar vi bort och l�gger till saker samt ritar om och f�rbereder f�r n�sta tick.
				G�r inga h�ndelsehanteringar efter denna punkt!
				*/


				prepareNextTick();

			} //k�r denna kod om vi kommit fram till n�sta tick
			else {
				SDL_Delay(nextTick - now);
			} //v�nta tills n�sta tick
		} //yttre while

	} //run

	void GameEngine::collisionDetection() {
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
	bool GameEngine::checkCollision(shared_ptr<Sprite> a, shared_ptr<Sprite> b) { //returns true if objects collided.
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

	void GameEngine::npcEvents() {

	}

	void GameEngine::prepareNextTick() {

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

		removed.clear(); //nu n�r vi tagit bort allt rensar vi removed s� vi kan anv�nda p� nytt i n�sta ticks.

		//L�gger till saker som tillkommit under h�ndelsef�rloppet
		for (shared_ptr<Sprite> s : added) {
			sprites.push_back(s);
		}
		while (!added.empty()) {
			added.pop_back();
		}

		//beh�ver rita alla komponenter, ifall n�got event �ndrar p� n�gon grafik.
		SDL_RenderClear(sys.getRen()); //Beh�ver f�rst rensa allt gammalt om man ska rita p� nytt
		//nu g�r vi igenom alla komponenter och ritar ut dem
		//cout << "END loop, DRAW" << endl;
		for (shared_ptr<Sprite> s : sprites)
			s->draw();
		SDL_RenderPresent(sys.getRen());

		//k�r gravitation inf�r n�sta tick, f�rutsatt att gravitationen �r p�
		if (gravity) {
			runGravity();
		}

		nextTick += (1000 / maxFps);
	}

	void GameEngine::runGravity() {
		for (shared_ptr<Sprite> s : sprites) {
			if (s->isAffectedByGravity()) {
				s->fall(gravityStrength);
			}
		}
	}

	void GameEngine::checkHotkeys(SDL_Event &event) {
		for (shared_ptr<Hotkey> h : hotkeys) {
			//cout << "Inside Loop" << endl;
			if (event.key.keysym.sym == h->getKey()) {
				//cout << "Key Matched" << endl;
				h->perform();
			}
		}
	}

	bool GameEngine::handleEvents() { //returns TRUE if quit should be true
		while (SDL_PollEvent(&event)) {
			//l�ng switchsats som kollar eventh�ndelser.
			switch (event.type) {
			case SDL_QUIT: return true;
			case SDL_MOUSEBUTTONDOWN:
				for (shared_ptr<Sprite> s : sprites) //kan va auto
					s->mouseDown(event); //funk i component som kollar om eventet �r till sig.
			case SDL_MOUSEBUTTONUP:
				for (shared_ptr<Sprite> s : sprites)
					s->mouseUp(event);
			case SDL_KEYDOWN: 
				for (shared_ptr<Sprite> s : sprites)
					s->keyDown(event);
			case SDL_KEYUP:
				for (shared_ptr<Sprite> s : sprites)
					s->keyUp(event);
			default: {
				checkHotkeys(event);
				break;
			}
			} //switch

		} //inre while (spelar h�ndelser)
		return false;
	}

} //cwing