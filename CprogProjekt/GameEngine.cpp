#include "GameEngine.h"
#include <SDL.h>
#include "System.h"
#include "Sprite.h"
#include "MovableSprite.h"
#include "StationarySprite.h"
#include "AnimatedSprite.h"
#include "TextBox.h"

#include <iostream>
#include <memory>



namespace cwing {
	GameEngine::GameEngine(std::vector<std::shared_ptr<Hotkey>> keys, std::vector<std::shared_ptr<Level>> lvls, int max_Fps, int min_Fps)
	{
		//loadGame(gameToLoad);
		hotkeys = keys;
		levels = lvls;
		maxFps = max_Fps;
		minFps = min_Fps;
		loadLevel(levels.at(0));
	}

	/*void GameEngine::loadGame(std::shared_ptr<Game> gameToLoad) {
		currentGame = gameToLoad;
		hotkeys = currentGame->getHotkeys();
		loadLevel(currentGame->getLevels().at(0));
		textbox = currentGame->getTextBox();
	}*/

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
		/*while (!sprites.empty()) {
			sprites.pop_back();
		}
		while (!added.empty()) {
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
				currentLevel->tick(paused); //kör tick-metod inuti leveln, inklusive ritar ut objekt
				if (currentLevel->levelCompleted()) {
					unsigned int index = 1;
					for (shared_ptr<Level> l : levels) {
						if (currentLevel == levels.at(index - 1)) {
							break;
						}
						index++;
					}
					if (levels.size() > index) {
						loadLevel(levels.at(index));
					} 
					else {
						cout << "You completed the game!";
						break;
					}
				}

				//textbox->draw();
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
				h->perform(paused);
			}
		}
	}

	bool GameEngine::handleEvents() { //returns TRUE if quit should be true
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: return true;
				case SDL_KEYDOWN:
					checkHotkeys(event);
					break;
			}
			for (shared_ptr<Sprite> s : currentLevel->getSprites()) {
				bool changePausState = s->handleInput(event, paused);
				if (changePausState) {
					cout << "paus";
					paused = !paused;
				}
			}
		}
		return false;
	}
	/*void GameEngine::nextLevel() {
		currentLevel++;
	}*/
} //cwing