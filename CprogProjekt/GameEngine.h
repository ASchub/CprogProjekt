#pragma once
#include "Sprite.h"
#include "Hotkey.h"
#include "Level.h"

#include <vector>
#include <memory>

using namespace std;

namespace cwing {
	class GameEngine
	{
	public:
		GameEngine(int maxFps = 70, int minFps = 5);
		void add(shared_ptr<Sprite> s); //lägger till sprites i loopen
		void add(shared_ptr<Hotkey> h);
		void add(shared_ptr<Level> l);
		void remove(shared_ptr<Sprite> s); //tar bort sprites från loopen
		void setMaxFps(int i); //sätter eget maxFps
		void setMinFps(int i); //sätter eget minFps
		void run(); //startar spelloopen
		void nextLevel();
		void addPlayer(shared_ptr<Sprite> p);
		~GameEngine();
	private:
		bool handleEvents(); //returns TRUE if quit should be true
		void checkHotkeys(SDL_Event &event);
		std::vector<shared_ptr<Hotkey>> hotkeys;
		std::vector<shared_ptr<Sprite>> sprites; //behöver vara pekare till sprite då det är en superklass, om man skickar en subklass och den tar emot hela objektet slicar den ned objektet till enbart sprite..
		std::vector<shared_ptr<Sprite>> added, removed; //för att ta bort saker under körning, skapar seperata vektorer för att hålla koll på vad som ska raderas/läggas på vid nästa tick
		std::vector<shared_ptr<Level>> levels;
		int maxFps;
		int minFps;
		SDL_Event event;
		int currentLevel = 0; // starts at 0, updates when level is updated
		shared_ptr<Sprite> player;

		Uint32 nextTick = SDL_GetTicks(); //initiellt värde, uppdateras varje tick
		Uint32 now;
	};

} //cwing
