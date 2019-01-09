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
		void add(shared_ptr<Sprite> s); //l�gger till sprites i loopen
		void add(shared_ptr<Hotkey> h);
		void add(shared_ptr<Level> l);
		void remove(shared_ptr<Sprite> s); //tar bort sprites fr�n loopen
		void setMaxFps(int i); //s�tter eget maxFps
		void setMinFps(int i); //s�tter eget minFps
		void run(); //startar spelloopen
		void nextLevel();
		void addPlayer(shared_ptr<Sprite> p);
		~GameEngine();
	private:
		bool handleEvents(); //returns TRUE if quit should be true
		void checkHotkeys(SDL_Event &event);
		std::vector<shared_ptr<Hotkey>> hotkeys;
		std::vector<shared_ptr<Sprite>> sprites; //beh�ver vara pekare till sprite d� det �r en superklass, om man skickar en subklass och den tar emot hela objektet slicar den ned objektet till enbart sprite..
		std::vector<shared_ptr<Sprite>> added, removed; //f�r att ta bort saker under k�rning, skapar seperata vektorer f�r att h�lla koll p� vad som ska raderas/l�ggas p� vid n�sta tick
		std::vector<shared_ptr<Level>> levels;
		int maxFps;
		int minFps;
		SDL_Event event;
		int currentLevel = 0; // starts at 0, updates when level is updated
		shared_ptr<Sprite> player;

		Uint32 nextTick = SDL_GetTicks(); //initiellt v�rde, uppdateras varje tick
		Uint32 now;
	};

} //cwing
