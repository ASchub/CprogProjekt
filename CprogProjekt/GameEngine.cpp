#include "GameEngine.h"
#include <SDL.h>
#include "System.h"

namespace cwing {

	GameEngine::GameEngine()
	{
	}

	/*
	Vectorerna försvinner automatiskt, men vi måste gå igenom vectorn och radera allt innehåll
	added, removed bör alltid vara tomma om avstängning kallats, men ifall något gick fel mitt i går vi även igenom dem...
	*/
	GameEngine::~GameEngine() 
	{
		for (Sprite *s : sprites) //kan va auto
			delete s;
		for (Sprite *s : added) 
			delete s;
		for (Sprite *s : removed) 
			delete s;
	}

	void GameEngine::add(Sprite* s) {
		added.push_back(s);
	}

	void GameEngine::remove(Sprite *s) {
		removed.push_back(s);
	}

	void GameEngine::run() {
		SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
		bool quit = false; //styr när huvudloopen ska avbrytas.

		while (!quit) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				//lång switchsats som kollar eventhändelser.
				switch (event.type) {
				case SDL_QUIT: quit = true; break;
				case SDL_MOUSEBUTTONDOWN:
					for (Sprite* s : sprites) //kan va auto
						s->mouseDown(event); //funk i component som kollar om eventet är till sig.
				case SDL_MOUSEBUTTONUP:
					for (Sprite* s : sprites)
						s->mouseUp(event);
				case SDL_KEYDOWN:
					for (Sprite* s : sprites)
						s->keyDown(event);
				case SDL_KEYUP:
					for (Sprite* s : sprites)
						s->keyUp(event);

				} //switch



			} //inre while (spelar händelser)

			/*
			Här ELLER ovanför inre while borde andra händelser ske, som att fiender rör sig m.m.
			Detta markerar slutet på interaktioner, efter detta tar vi bort och lägger till saker samt ritar om och förbereder för nästa tick.
			Gör inga händelsehanteringar efter denna punkt!
			*/

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

			removed.clear(); //nu när vi tagit bort allt rensar vi removed så vi kan använda på nytt i nästa ticks.

			//Lägger till saker som tillkommit under händelseförloppet
			for (Sprite* s : added) {
				sprites.push_back(s);
			}

			//behöver rita alla komponenter, ifall något event ändrar på någon grafik.
			SDL_RenderClear(sys.getRen()); //Behöver först rensa allt gammalt om man ska rita på nytt
			//nu går vi igenom alla komponenter och ritar ut dem
			for (Sprite* s : sprites)
				s->draw();
			SDL_RenderPresent(sys.getRen());

		} //yttre while


	}

} //cwing