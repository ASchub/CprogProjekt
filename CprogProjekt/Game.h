#pragma once

#include "Sprite.h"
#include "MovableSprite.h"
#include "Hotkey.h"
#include "TextBox.h"
#include "Level.h"

class Game
{
public:
	Game();
	~Game();
	void initGame();
	std::vector<std::shared_ptr<cwing::Level>> getLevels() { return levels; }
	std::vector<std::shared_ptr<cwing::Hotkey>> getHotkeys() { return hotkeys; }
private:
	std::shared_ptr<cwing::MovableSprite> player;
	std::vector<std::shared_ptr<cwing::Level>> levels;
	std::vector<std::shared_ptr<cwing::Hotkey>> hotkeys;
	void addLevels();
	void addHotkeys();
	void createPlayer();
};

