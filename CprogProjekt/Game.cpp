#include "Game.h"
#include "AnimatedSprite.h"
#include "MovableSprite.h"
#include "StationarySprite.h"
#include "Hotkey.h"
#include "Level.h"
#include "FunctionHotkey.h"
#include "MemberHotkey.h"
#include "TextBox.h"
#include <memory>

using namespace cwing;

/*
Create subclass of MovableSprite so we can make a general mouseDown handler 
for the player controlled character, here it just prints to console.
*/
class Player : public MovableSprite {
public:
	static shared_ptr<Player> getInstance() {
		return shared_ptr<Player>(new Player(200, 200, "./media/p1.bmp"));
	}
	void handleInput(const SDL_Event& event) {
		if(event.type == SDL_MOUSEBUTTONDOWN)
			cout << "MouseDown registered" << endl;
	}
protected:
	Player(int x, int y, const char path[]) : MovableSprite(x, y, path) {}
};

/*
Create subclass of MovableSprite, to define specific handleCollision for apple objects.
AppleSprites are collected in order to win the level, they delete themselves on collision,
and have an automatic behaviour to make them constantly move downwards.
*/
class AppleSprite : public MovableSprite {
public:
	static shared_ptr<AppleSprite> getInstance(int x = 700, int y=0) {
		return shared_ptr<AppleSprite>(new AppleSprite(x, y, "./media/apple.bmp"));
	}
	void handleCollision(std::shared_ptr<SDL_Rect> intersection) {
		deleteMe();
	}
	void automaticBehaviour() {
		fall(2);
	}

protected:
	AppleSprite(int x, int y, const char path[]) : MovableSprite(x, y, path) {}
};

/*
Create subclass of Level, to define specific win-condition.
*/
class AppleLevel : public Level {
public:
	static std::shared_ptr<AppleLevel> getInstance(bool gravity, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea) {
		return std::shared_ptr<AppleLevel>(new AppleLevel(gravity, downwardsMotion, gameArea));
	}

	static std::shared_ptr<AppleLevel> getInstance() {
		std::shared_ptr<SDL_Rect> gameArea = std::shared_ptr<SDL_Rect>(new SDL_Rect());
		gameArea->w = 800;
		gameArea->h = 600;
		gameArea->x = 0;
		gameArea->y = 0;
		return std::shared_ptr<AppleLevel>(new AppleLevel(false, 0, gameArea));
	}
protected:
	AppleLevel(bool gravityOn, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea) : Level(gravityOn, downwardsMotion, gameArea){ }
	void completeLevel() {
		int apples = 0;
		for (shared_ptr<Sprite> s : sprites) {
			if (dynamic_pointer_cast<AppleSprite>(s)) {
				apples++;
				break;
			}
		}
		if(apples == 0)
			completed = true;
	}

};

//Game functions {
	Game::Game()
	{
		initGame();
	}

	void Game::initGame() {
		createPlayer();
		addLevels();
		addHotkeys();
	}

	/*
	Initializes levels, as well as the sprites for each level, and adds the Level objects to the level vector
	*/
	void Game::addLevels() {
		std::shared_ptr<AppleLevel> level = shared_ptr<AppleLevel>(AppleLevel::getInstance());
		level->setGravity(true, 5);
		level->add(StationarySprite::getInstance(0, 100, "./media/platform.bmp"));
		level->add(StationarySprite::getInstance(200, 350, "./media/platform.bmp"));
		level->add(StationarySprite::getInstance(100, 600, "./media/platform.bmp"));
		level->add(player);
		level->add(TextBox::getInstance(0, 0, "./media/TextBox.bmp"));
		level->add(AppleSprite::getInstance());
		levels.push_back(level);

		std::shared_ptr<AppleLevel> level2 = shared_ptr<AppleLevel>(AppleLevel::getInstance());
		level2->add(StationarySprite::getInstance(100, 100, "./media/tree.bmp"));
		level2->add(StationarySprite::getInstance(500, 100, "./media/tree.bmp"));
		level2->add(player);
		level2->add(AnimatedSprite::getInstance(500, 500, 14, 20, 7, "./media/flamesheet.bmp"));
		level2->add(AppleSprite::getInstance());
		level2->add(AppleSprite::getInstance(0, 300));
		levels.push_back(level2);
		
	}

	/*
	Initializes hotkeys and adds them to the hotkeys vector
	*/
	void Game::addHotkeys() {
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_UP, player, &Player::moveUp));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_DOWN, player, &Player::moveDown));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_RIGHT, player, &Player::moveRight));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_LEFT, player, &Player::moveLeft));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_SPACE, player, &Player::jump));
	}
	
	/*
	Initializes the Player object
	*/
	void Game::createPlayer() {
		player = Player::getInstance();
		player->setAffectedByGravity(true);
		player->setBounces(5);
	}

	Game::~Game()
	{
	}
// }
