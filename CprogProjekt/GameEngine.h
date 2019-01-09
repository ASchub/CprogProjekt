#pragma once
#include "Sprite.h"
#include "Hotkey.h"

#include <vector>
#include <memory>

using namespace std;

namespace cwing {
	class GameEngine
	{
	public:
		GameEngine();
		void add(shared_ptr<Sprite> s); //l�gger till sprites i loopen
		void add(shared_ptr<Hotkey> h);
		void remove(shared_ptr<Sprite> s); //tar bort sprites fr�n loopen
		void setMaxFps(int i); //s�tter eget maxFps
		void setMinFps(int i); //s�tter eget minFps
		void run(); //startar spelloopen
		void setGravity(bool g, int downwardsMotion) { gravity = g; gravityStrength = downwardsMotion; } //Boolean to determine if the game engine should have gravity or not, downwardsMotion is nr of pixels down per tick
		bool getGravity() { return gravity; }
		~GameEngine();
	private:
		bool handleEvents(); //returns TRUE if quit should be true
		void prepareNextTick();
		void npcEvents();
		void collisionDetection();
		bool checkCollision(shared_ptr<Sprite> A, shared_ptr<Sprite> B);
		void checkHotkeys();
		void runGravity();
		std::vector<shared_ptr<Hotkey>> hotkeys;
		std::vector<shared_ptr<Sprite>> sprites; //beh�ver vara pekare till sprite d� det �r en superklass, om man skickar en subklass och den tar emot hela objektet slicar den ned objektet till enbart sprite..
		std::vector<shared_ptr<Sprite>> added, removed; //f�r att ta bort saker under k�rning, skapar seperata vektorer f�r att h�lla koll p� vad som ska raderas/l�ggas p� vid n�sta tick
		int maxFps;
		int minFps;
		SDL_Event event;
		bool gravity = false;
		int gravityStrength = 0;
	};
} //cwing
