#pragma once

#include "Sprite.h"
#include "MovableSprite.h"
#include "Hotkey.h"
#include "TextBox.h"
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
	std::shared_ptr<TextBox> getTextBox() { return textbox; }
	private:
		std::shared_ptr<MovableSprite> player;
		std::vector<std::shared_ptr<Level>> levels;
		std::vector<std::shared_ptr<Hotkey>> hotkeys;
		std::shared_ptr<TextBox> textbox;
		void addLevels();
		void addHotkeys();
		void createPlayer();
	};
} //cwing

