#pragma once
#include "Sprite.h"
#include "Hotkey.h"
#include "Level.h"
#include "Game.h"
#include "TextBox.h"

#include <vector>
#include <memory>

namespace cwing {
	class GameEngine
	{
	public:
		//GameEngine(std::shared_ptr<TextBox> tb, std::vector<std::shared_ptr<Hotkey>> keys, std::vector<std::shared_ptr<Level>> lvls, int maxFps = 70, int minFps = 5);
		GameEngine(std::vector<std::shared_ptr<Hotkey>> keys, std::vector<std::shared_ptr<Level>> lvls, int maxFps = 70, int minFps = 5);
		void add(std::shared_ptr<Sprite> s); //l�gger till sprites i loopen
		void add(std::shared_ptr<Hotkey> h); //l�gger till hotkeys
		void add(std::shared_ptr<Level> l);	//l�gger till levels
		void remove(std::shared_ptr<Sprite> s); //tar bort sprites fr�n loopen
		//void remove(shared_ptr<Hotkey> h);  //TODO: should implement this...
		void setMaxFps(int i); //s�tter eget maxFps
		void setMinFps(int i); //s�tter eget minFps
		void run(); //startar spelloopen
		//void nextLevel();
		void addPlayer(std::shared_ptr<Sprite> p); //l�gger till spelarobjekt
		~GameEngine();
	private:
		bool handleEvents(); //returns TRUE if quit should be true
		void checkHotkeys(SDL_Event &event);
		std::vector<std::shared_ptr<Hotkey>> hotkeys;
		std::vector<std::shared_ptr<Level>> levels;
		//std::shared_ptr<TextBox> textbox;
		//std::vector<std::shared_ptr<Sprite>> sprites; //beh�ver vara pekare till sprite d� det �r en superklass, om man skickar en subklass och den tar emot hela objektet slicar den ned objektet till enbart sprite..
		//std::vector<shared_ptr<Sprite>> added, removed; //f�r att ta bort saker under k�rning, skapar seperata vektorer f�r att h�lla koll p� vad som ska raderas/l�ggas p� vid n�sta tick
		//std::vector<shared_ptr<Level>> levels;
		std::shared_ptr<Game> currentGame;
		std::shared_ptr<Level> currentLevel;
		void loadLevel(std::shared_ptr<Level> levelToLoad);
		//void loadGame(std::shared_ptr<Game> gameToLoad);
		int maxFps;
		int minFps;
		//bool inputText = false;
		bool paused = false;
		SDL_Event event;
		//int currentLevel = 0; // starts at 0, updates when level is updated
		std::shared_ptr<Sprite> player;

		Uint32 nextTick = SDL_GetTicks(); //initiellt v�rde, uppdateras varje tick
		Uint32 now;
	};

} //cwing
