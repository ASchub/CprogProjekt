#pragma once
#include "MovableSprite.h"
#include <memory>
#include "GameEngine.h"
#include "Sprite.h"


namespace cwing {
	class Game
	{
	public:
		Game(std::shared_ptr<GameEngine> e);
		~Game();
		void initGame();

	private:
		std::shared_ptr<GameEngine> engine;
		std::shared_ptr<MovableSprite> player;
		bool gravity;
		int downWardsMotion;
		void addLevels();
		//void addSprites();
		void addHotkeys();
		void createPlayer();
	};
} //cwing

