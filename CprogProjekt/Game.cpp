#include "Game.h"
#include "AnimatedSprite.h"
#include "MovableSprite.h"
#include "StationarySprite.h"
#include "Hotkey.h"
#include "FunctionHotkey.h"
#include "MemberHotkey.h"
#include <memory>





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

	// Create subclass of MovableSprite so we can make a general mouseDown handler for the player controlled character, here it just prints to console.
	class Player : public MovableSprite {
	public:
		void mouseDown(const SDL_Event& event) {
			cout << "MouseDown registered" << endl;
		}
	};

	Game::Game()
	{
		initGame();
	}

	void Game::initGame() {
		createPlayer();
		addLevels();
		addHotkeys();
	}

	void Game::addLevels() {
		std::shared_ptr<Level> level = shared_ptr<Level>(Level::getInstance());
		level->add(StationarySprite::getInstance(100, 100, "./media/tree.bmp"));
		level->add(StationarySprite::getInstance(500, 100, "./media/tree.bmp"));
		level->add(player);
		level->add(AnimatedSprite::getInstance(500, 500, 14, 20, 7, "./media/flamesheet.bmp"));
		levels.push_back(level);


		std::shared_ptr<Level> level2 = shared_ptr<Level>(Level::getInstance());
		level2->setGravity(true, 5);
		level2->add(StationarySprite::getInstance(0, 100, "./media/platform.bmp"));
		level2->add(StationarySprite::getInstance(200, 350, "./media/platform.bmp"));
		level2->add(StationarySprite::getInstance(100, 600, "./media/platform.bmp"));
		level2->add(player);
		//level2->add(AnimatedSprite::getInstance(300, 300, 14, 20, 7, "./media/flamesheet.bmp"));
		levels.push_back(level2);
		
	}

	void Game::addHotkeys() {
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_UP, player, &MovableSprite::moveUp));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_DOWN, player, &MovableSprite::moveDown));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_RIGHT, player, &MovableSprite::moveRight));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_LEFT, player, &MovableSprite::moveLeft));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDLK_SPACE, player, &MovableSprite::jump));
		hotkeys.push_back(MemberHotkey<MovableSprite>::getInstance(SDL_MOUSEBUTTONDOWN, player, &MovableSprite::jump));
		
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
		player = MovableSprite::getInstance(200, 200, "./media/p1.bmp");
		player->setAffectedByGravity(true);
		player->setBounces(5);
	}

	Game::~Game()
	{
	}
}
