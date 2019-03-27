#include <SDL.h>
#include "GameEngine.h"
#include "Game.h"

#include <string>
#include <iostream>
#include <memory>


using namespace std;
using namespace cwing;



int main(int argc, char** argv) {
	/*
	GameEngine is a class part of our package which handles everything, you send it a vector of Hotkeys and a vector of Levels and min/max fps.
	calling GameEngine.run() will initiate the game loop.
	Each level has several sprites inside them.

	Game is a class created by the programmer using our package, it is just a collection of things necesarry to set up a game using the GameEngine.
	*/
	shared_ptr<Game> game = shared_ptr<Game>(new Game());
	shared_ptr<GameEngine> ge = shared_ptr<GameEngine>(new GameEngine(game->getHotkeys(), game->getLevels(),70,5));
	ge->run();

	return 0;
}
