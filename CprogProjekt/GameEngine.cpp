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
	GameEngine::GameEngine(std::shared_ptr<Game> gameToLoad, int max_Fps, int min_Fps)
	{
		loadGame(gameToLoad);
		maxFps = max_Fps;
		minFps = min_Fps;
		loadLevel(gameToLoad->getLevels().at(1));
	}

	void GameEngine::loadGame(std::shared_ptr<Game> gameToLoad) {
		currentGame = gameToLoad;
		hotkeys = currentGame->getHotkeys();
		loadLevel(currentGame->getLevels().at(0));
	}

	void GameEngine::loadLevel(std::shared_ptr<Level> levelToLoad) {
		currentLevel = levelToLoad;
		//sprites = levelToLoad->getSprites();
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
		/*while (!added.empty()) {
			added.pop_back();
		}
		while (!removed.empty()) {
			removed.pop_back();
		}*/
	}

	void GameEngine::add(shared_ptr<Sprite> s) {
		cout << "sprite" << endl;
		currentLevel->add(s);
	}

	void GameEngine::add(shared_ptr<Hotkey> h) {
		cout << "hotkey" << endl;
		hotkeys.push_back(h);
	}

	/*void GameEngine::add(shared_ptr<Level> l) {
		cout << "level" << endl;
		levels.push_back(l);
	}*/

	void GameEngine::addPlayer(shared_ptr<Sprite> p) {
		player = p;
	}

	void GameEngine::remove(shared_ptr<Sprite> s) {
		currentLevel->remove(s);
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
				currentLevel->tick(); //kör tick-metod inuti leveln, inklusive ritar ut objekt
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

	void GameEngine::inputText() { //TODO
		bool done = false;
		bool renderText = false;
		SDL_StartTextInput;
		while (!done) {
			SDL_Event event;
			if (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDLK_KP_ENTER:
					/* Quit */
					done = true;
					break;
				case SDLK_BACKSPACE:
					if ()
						break;
				case SDL_TEXTINPUT:
					/* Add new text onto the end of our text */
					
					break;
				case SDL_TEXTEDITING:
					/*
					Update the composition text.
					Update the cursor position.
					Update the selection length (if any).
					*/

					break;
				}
			}
			SDL_RenderClear(sys.getRen());
			SDL_RenderPresent(sys.getRen());
		}
	} //ENDTODO

	bool GameEngine::handleEvents() { //returns TRUE if quit should be true
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return true;
			checkHotkeys(event);
		} //while
		return false;
	}

	/*void GameEngine::nextLevel() {
		currentLevel++;
	}*/
} //cwing