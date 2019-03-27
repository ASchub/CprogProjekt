#pragma once

#include "Sprite.h"
#include "MovableSprite.h"
#include "Hotkey.h"
#include "TextBox.h"
#include "Level.h"
/*
Class for collecting data, is not a part of the Game Engine
Created to simplify implementing the specific game.
*/
class Game
{
public:
	/*
	Constructor and Destructor
	*/
	Game();
	~Game();
	
	/*
	Method to call the private methods for data initialization
	*/
	void initGame();
	
							/*
	Getters
	*/
	std::vector<std::shared_ptr<cwing::Level>> getLevels() { return levels; }
	std::vector<std::shared_ptr<cwing::Hotkey>> getHotkeys() { return hotkeys; }
private:
	/*
	Private variables and vectors for datastorage
	*/
	std::shared_ptr<cwing::MovableSprite> player;
	std::vector<std::shared_ptr<cwing::Level>> levels;
	std::vector<std::shared_ptr<cwing::Hotkey>> hotkeys;
	
	/*
	Methods for initializing data
	*/
	void addLevels();
	void addHotkeys();
	void createPlayer();
};

