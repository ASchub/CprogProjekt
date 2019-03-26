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
		void tick();
		Level(const Level&) = delete; //Copy-konstruktorn, skall inte finnas pga värdesemantik
		const Level& operator=(const Sprite&) = delete; //ingen operatoröverlagring
		std::vector<shared_ptr<Sprite>> getSprites() { return sprites; }

		//gravity stuff
		void setGravity(bool g, int downwardsMotion);
		bool getGravity() { return &gravity; }

	protected:
		Level(bool gravityOn, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea); //Konstruktor

	private:
		std::vector<shared_ptr<Sprite>> sprites;
		std::vector<shared_ptr<Sprite>> added, removed;

		std::shared_ptr<SDL_Rect> playableArea;

		//gravity stuff
		void runGravity();
		void prepareNextTick();
		bool gravity;
		int gravityStrength;

	};
} //cwing