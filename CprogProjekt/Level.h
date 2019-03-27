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
		Level(const Level&) = delete; //Copy-konstruktorn, skall inte finnas pga v�rdesemantik
		const Level& operator=(const Sprite&) = delete; //ingen operator�verlagring
		std::vector<shared_ptr<Sprite>> getSprites() { return sprites; }
		bool levelCompleted() const { return completed; };
		//gravity stuff
		void setGravity(bool g, int downwardsMotion);
		bool getGravity() { return &gravity; }

	protected:
		Level(bool gravityOn, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea); //Konstruktor

		// �verskugga denna metod f�r att best�mma n�r en level ska bytas, genom att s�tta "completed = true" kommer n�sta level laddas vid n�sta tick.
		virtual void completeLevel() { }

		std::vector<shared_ptr<Sprite>> sprites; //minnesl�ckage?
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