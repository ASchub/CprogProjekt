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
	

	Game::Game(std::shared_ptr<GameEngine> e)
	{
		engine = e;
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
		engine->add(level);


		std::shared_ptr<Level> level2 = shared_ptr<Level>(Level::getInstance());
		level2->add(StationarySprite::getInstance(0, 100, "./media/tree.bmp"));
		level2->add(StationarySprite::getInstance(400, 100, "./media/tree.bmp"));
		level2->add(StationarySprite::getInstance(400, 600, "./media/tree.bmp"));
		level2->add(player);
		level2->add(AnimatedSprite::getInstance(300, 300, 14, 20, 7, "./media/flamesheet.bmp"));
		engine->add(level2);
		
	}

	void Game::addHotkeys() {
		engine->add(MemberHotkey<MovableSprite>::getInstance(SDLK_UP, player, &MovableSprite::moveUp));
		engine->add(MemberHotkey<MovableSprite>::getInstance(SDLK_DOWN, player, &MovableSprite::moveDown));
		engine->add(MemberHotkey<MovableSprite>::getInstance(SDLK_RIGHT, player, &MovableSprite::moveRight));
		engine->add(MemberHotkey<MovableSprite>::getInstance(SDLK_LEFT, player, &MovableSprite::moveLeft));

		//hotkey testing, using SPACE, F, M
		std::shared_ptr<TestHotkey> h = shared_ptr<TestHotkey>(new TestHotkey());
		engine->add(h);

		std::shared_ptr<FunctionHotkey> fh = FunctionHotkey::getInstance(SDLK_f, testFuncHotkey);
		engine->add(fh);

		std::shared_ptr<MemberHotkey<Hotkey>> mh = MemberHotkey<Hotkey>::getInstance(SDLK_m, fh, &Hotkey::perform);
		engine->add(mh);
	}

	void Game::createPlayer() {
		player = MovableSprite::getInstance(300, 100, "./media/gubbe.bmp");
		engine->addPlayer(player);
	}

	Game::~Game()
	{
	}
}
