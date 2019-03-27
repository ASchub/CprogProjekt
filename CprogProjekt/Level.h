#pragma once
#include "Sprite.h"
#include "Hotkey.h"

#include <vector>
#include <memory>

namespace cwing {
	class Level
	{
	public:
		~Level(); //Destruktor
		static std::shared_ptr<Level> getInstance(bool gravity, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea);
		static std::shared_ptr<Level> getInstance();
		void add(std::shared_ptr<Sprite> s);
		void remove(std::shared_ptr<Sprite> s);
		void tick(bool gameIsPaused);
		Level(const Level&) = delete; //Copy-konstruktorn, skall inte finnas pga värdesemantik
		const Level& operator=(const Sprite&) = delete; //ingen operatoröverlagring
		std::vector<shared_ptr<Sprite>> getSprites() { return sprites; }
		bool levelCompleted() const { return completed; };
		//gravity stuff
		void setGravity(bool g, int downwardsMotion);
		bool getGravity() { return &gravity; }

	protected:
		Level(bool gravityOn, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea); //Konstruktor

		// överskugga denna metod för att bestämma när en level ska bytas, genom att sätta "completed = true" kommer nästa level laddas vid nästa tick.
		virtual void completeLevel() { }

		std::vector<shared_ptr<Sprite>> sprites; //minnesläckage?
		std::vector<shared_ptr<Sprite>> added, removed;

		std::shared_ptr<SDL_Rect> playableArea;
		bool completed = false;

	private:




		//gravity stuff
		void runGravity();
		void prepareNextTick(bool gameIsPaused);
		bool gravity;
		int gravityStrength;

	};
} //cwing