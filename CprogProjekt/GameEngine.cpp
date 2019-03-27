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
		hotkeys = keys;
		levels = lvls;
		maxFps = max_Fps;
		minFps = min_Fps;
		loadLevel(levels.at(0));
	}

	void GameEngine::loadLevel(std::shared_ptr<Level> levelToLoad) {
		currentLevel = levelToLoad;
	}

	GameEngine::~GameEngine()
	{
	}

	void GameEngine::setMaxFps(int i) {
		maxFps = i;
	}

	void GameEngine::setMinFps(int i) {
		minFps = i;
	}

	void GameEngine::run() {
		SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
		bool quit = false;						//Determines when the main game loop should break

		while (!quit) {
			now = SDL_GetTicks();

			if (nextTick <= now) {
				quit = handleEvents();			//Handles all SDL_Events that have been registered since the last tick
				if (quit)						//Ends the loop if the event handler has determined that the game should shut down
					break;
				SDL_RenderClear(sys.getRen());
				currentLevel->tick(paused);				//Runs tick() inside of the current Level, which includes drawing all game objects
				if (currentLevel->levelCompleted()) {	//Controls if win-condition has been reached for the current level
					//Determines which level is next level
					unsigned int index = 1;
					for (shared_ptr<Level> l : levels) {
						if (currentLevel == levels.at(index - 1)) {
							break;
						}
						index++;
					}
					//If the index for next level is inside of the level vector, next level is loaded
					if (levels.size() > index) {
						loadLevel(levels.at(index));
					} 
					else {
						//Else the game shuts down
						cout << "You completed the game!";
						break;
					}
				}
				SDL_RenderPresent(sys.getRen());
				nextTick += (1000 / maxFps);		//Calculates when next tick will be
			} //This code runs if we have reached next tick
			else {
				SDL_Delay(nextTick - now);
			} //Else wait until next tick
		}

	}

	/*
	Runs perform() in all defined hotkeys that corresponds to the event parameter
	*/
	void GameEngine::checkHotkeys(SDL_Event &event) {
		for (shared_ptr<Hotkey> h : hotkeys) {
			if (event.key.keysym.sym == h->getKey()) {
				h->perform(paused);
			}
		}
	}

	/*
	Checks all events that have been received since last tick.
	Returns true if the program should shut down, else returns false.
	Calls checkHotkeys() for keydown, AND calls handleEvent() in all sprites.
	NOTE that if a hotkey and a sprite have both defined actions for certain conditions
	BOTH actions will be performed.
	*/
	bool GameEngine::handleEvents() {
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
} //cwing