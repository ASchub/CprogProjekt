#include <SDL.h>
#include "GameEngine.h"
#include "Game.h"

#include <string>
#include <iostream>
#include <memory>


using namespace std;
using namespace cwing;



int main(int argc, char** argv) {
	// "Game" �r en klass som till�mningsprogrameraren �r t�nkt ha skapat
	// GameEngine �r en klass som �r en del av v�rat paket.
	shared_ptr<Game> game = shared_ptr<Game>(new Game());
	shared_ptr<GameEngine> ge = shared_ptr<GameEngine>(new GameEngine(game,70,5));
	ge->run();

	return 0;
}
