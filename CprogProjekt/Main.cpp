#include <SDL.h>
#include "GameEngine.h"
#include "Game.h"

#include <string>
#include <iostream>
#include <memory>


using namespace std;
using namespace cwing;



int main(int argc, char** argv) {
	// "Game" är en klass som tillämningsprogrameraren är tänkt ha skapat
	// GameEngine är en klass som är en del av vårat paket.
	shared_ptr<Game> game = shared_ptr<Game>(new Game());
	shared_ptr<GameEngine> ge = shared_ptr<GameEngine>(new GameEngine(game,70,5));
	ge->run();

	return 0;
}
