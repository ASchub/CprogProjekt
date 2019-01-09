#include <SDL.h>
#include "GameEngine.h"
#include "Game.h"

#include <string>
#include <iostream>
#include <memory>


using namespace std;
using namespace cwing;



int main(int argc, char** argv) {
	shared_ptr<GameEngine> ge = shared_ptr<GameEngine>(new GameEngine(70,5));
	shared_ptr<Game> game = shared_ptr<Game>(new Game(ge));
	game->initGame();
	ge->run();

	return 0;
}
