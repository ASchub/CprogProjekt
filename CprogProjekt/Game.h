#pragma once

#include "Sprite.h"
#include "MovableSprite.h"
#include "Hotkey.h"
#include "Level.h"

#include <memory>


namespace cwing {
	class Game
	{
	public:
		Game();
		~Game();
		void initGame();
		std::vector<std::shared_ptr<Level>> getLevels() { return levels; }
		std::vector<std::shared_ptr<Hotkey>> getHotkeys() { return hotkeys; }
	private:
		std::shared_ptr<MovableSprite> player;
		std::vector<std::shared_ptr<Level>> levels;
		std::vector<std::shared_ptr<Hotkey>> hotkeys;
		void addLevels();
		void addHotkeys();
		void createPlayer();
	};
} //cwing

