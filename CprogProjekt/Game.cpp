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



// Create subclass of MovableSprite so we can make a general mouseDown handler for the player controlled character, here it just prints to console.
class Player : public cwing::MovableSprite {
public:
	static shared_ptr<Player> getInstance() {
		return shared_ptr<Player>(new Player(200, 200, "./media/p1.bmp"));
	}
	void mouseDown(const SDL_Event& event) {
		cout << "MouseDown registered" << endl;
	}
protected:
	Player(int x, int y, const char path[]) : MovableSprite(x, y, path) {}
};

class AppleSprite : public cwing::MovableSprite {
public:
	static shared_ptr<AppleSprite> getInstance(int x = 700, int y=0) {
		return shared_ptr<AppleSprite>(new AppleSprite(x, y, "./media/apple.bmp"));
	}
	void handleCollision(std::shared_ptr<SDL_Rect> intersection) {
		deleteMe();
	}
	void automaticBehaviour() {
		this->setXY(this->getRect()->x, (this->getRect()->y) + 2);
	}

protected:
	AppleSprite(int x, int y, const char path[]) : MovableSprite(x, y, path) {}
};

class AppleLevel : public cwing::Level {
public:
	static std::shared_ptr<AppleLevel> getInstance(bool gravity, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea) {
		return std::shared_ptr<AppleLevel>(new AppleLevel(gravity, downwardsMotion, gameArea));
	}

	static std::shared_ptr<AppleLevel> getInstance() {
		std::shared_ptr<SDL_Rect> gameArea = std::shared_ptr<SDL_Rect>(new SDL_Rect());
		gameArea->w = 800; //TODO - fixa så w och h är anpassade efter fönsterstorlek.
		gameArea->h = 600;
		gameArea->x = 0;
		gameArea->y = 0;
		return std::shared_ptr<AppleLevel>(new AppleLevel(false, 0, gameArea));
	}
protected:
	AppleLevel(bool gravityOn, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea) : Level(gravityOn, downwardsMotion, gameArea){ }
	void completeLevel() {
		int apples = 0;
		for (shared_ptr<cwing::Sprite> s : sprites) {
			if (dynamic_pointer_cast<AppleSprite>(s)) {
				apples++;
				break;
			}
		}
		if(apples == 0)
			completed = true;
	}

};




class TestHotkey : public Hotkey {
public:
	TestHotkey() :Hotkey(SDLK_SPACE) {}
	void perform() {
		cout << "Normal Hotkey working!" << endl;
	}
};

void testFuncHotkey() {
	cout << "Function Hotkey Working!" << endl;
}

namespace cwing {




	Game::Game()
	{
		initGame();
	}

	void Game::initGame() {
		createPlayer();
		addLevels();
		addHotkeys();
		//textbox = TextBox::getInstance(0, 0, "./media/TextBox.bmp");
	}

	void Game::addLevels() {



		std::shared_ptr<AppleLevel> level = shared_ptr<AppleLevel>(AppleLevel::getInstance());
		level->setGravity(true, 5);
		level->add(StationarySprite::getInstance(0, 100, "./media/platform.bmp"));
		level->add(StationarySprite::getInstance(200, 350, "./media/platform.bmp"));
		level->add(StationarySprite::getInstance(100, 600, "./media/platform.bmp"));
		level->add(player);
		level->add(TextBox::getInstance(0, 0, "./media/TextBox.bmp"));
		level->add(AppleSprite::getInstance());
		//level2->add(AnimatedSprite::getInstance(300, 300, 14, 20, 7, "./media/flamesheet.bmp"));
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

	void Game::addHotkeys() {
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_UP, player, &Player::moveUp));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_DOWN, player, &Player::moveDown));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_RIGHT, player, &Player::moveRight));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_LEFT, player, &Player::moveLeft));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_SPACE, player, &Player::jump));
		
		/*
		//hotkey testing, using SPACE, F, M
		std::shared_ptr<TestHotkey> h = shared_ptr<TestHotkey>(new TestHotkey());
		hotkeys.push_back(h);

		std::shared_ptr<FunctionHotkey> fh = FunctionHotkey::getInstance(SDLK_f, testFuncHotkey);
		hotkeys.push_back(fh);

		std::shared_ptr<MemberHotkey<Hotkey>> mh = MemberHotkey<Hotkey>::getInstance(SDLK_m, fh, &Hotkey::perform);
		hotkeys.push_back(mh);*/
	}

	void Game::createPlayer() {
		//(200, 200, "./media/p1.bmp")
		player = Player::getInstance();
		player->setAffectedByGravity(true);
		player->setBounces(5);
	}

	Game::~Game()
	{
	}
}
