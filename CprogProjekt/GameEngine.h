#pragma once
#include "Sprite.h"
#include "Hotkey.h"
#include "Level.h"
#include "Game.h"
#include "TextBox.h"

#include <vector>
#include <memory>

namespace cwing {
	class GameEngine
	{
	public:
		/*
		Constructor:
		Takes vectors for hotkeys and levels arguments,
		as well as variables for max and min FPS.
		The FPS variables have default values that are used if
		no other values are defined.
		*/
		GameEngine(std::vector<std::shared_ptr<Hotkey>> keys, std::vector<std::shared_ptr<Level>> lvls, int maxFps = 70, int minFps = 5);

		/*
		Setters for FPS
		*/
		void setMaxFps(int i);
		void setMinFps(int i);

		/*
		Runs the game loop
		*/
		void run();

		/*
		Destructor
		*/
		~GameEngine();

	private:
		/*
		Method to load the current level.
		*/
		void loadLevel(std::shared_ptr<Level> levelToLoad);

		/*
		Methods to handle events that are triggered inside the game loop
		*/
		bool handleEvents();						//returns TRUE if game should shut down
		void checkHotkeys(SDL_Event &event);

		/*
		Private variables for game objects and hotkeys
		*/
		std::vector<std::shared_ptr<Hotkey>> hotkeys;
		std::vector<std::shared_ptr<Level>> levels;
		std::shared_ptr<Level> currentLevel;
		std::shared_ptr<Sprite> player;
		/*
		Private variables for game state and FPS
		*/
		int maxFps;
		int minFps;
		bool paused = false;
		SDL_Event event;
		
		/*
		Private variables for FPS-control
		*/
		Uint32 nextTick = SDL_GetTicks();	//Initial value, updates every tick
		Uint32 now;							//Updates every tick
	};

} //cwing
