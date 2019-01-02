#pragma once
#include <vector>
#include "Sprite.h"

namespace cwing {
	class GameEngine
	{
	public:
		GameEngine();
		void add(Sprite*); //lägger till sprites i loopen
		void remove(Sprite*); //tar bort sprites från loopen
		void run(); //startar spelloopen
		~GameEngine();
	private:
		bool handleEvents(); //returns TRUE if quit should be true
		void prepareNextTick();
		void npcEvents();
		void collisionDetection();
		std::vector<Sprite*> sprites; //behöver vara pekare till sprite då det är en superklass, om man skickar en subklass och den tar emot hela objektet slicar den ned objektet till enbart sprite..
		std::vector<Sprite*> added, removed; //för att ta bort saker under körning, skapar seperata vektorer för att hålla koll på vad som ska raderas/läggas på vid nästa tick

	};

} //cwing
