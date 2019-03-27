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
		/*
		The constructor takes three arguments:
		gravity and downwardsmotion are variables affecting physics (A-grade task not implemented properly), just leave as "false" and "0" for now.
		gameArea is the size of the level.

		the default constuctor automatically sets the game area to 800*600
		*/
		static std::shared_ptr<Level> getInstance(bool gravity, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea);
		static std::shared_ptr<Level> getInstance();

		/*
		add & remove:
		adds or removes a sprite from the level
		*/
		void add(std::shared_ptr<Sprite> s);
		void remove(std::shared_ptr<Sprite> s);

		/*
		tick:
		called once every tick, which in turn calls all sprites in this levels tick() function.
		*/
		void tick(bool gameIsPaused);

		Level(const Level&) = delete; //Copy-konstruktorn, skall inte finnas pga värdesemantik
		const Level& operator=(const Sprite&) = delete; //ingen operatoröverlagring

		/*
		getters and setters
		*/
		std::vector<shared_ptr<Sprite>> getSprites() { return sprites; }
		bool levelCompleted() const { return completed; };
		// A-grade things we did not have time to implement correctly {
		void setGravity(bool g, int downwardsMotion);
		bool getGravity() { return &gravity; }
		// }

	protected:
		Level(bool gravityOn, int downwardsMotion, std::shared_ptr<SDL_Rect> gameArea); //Konstruktor

		/*
		Overshadow this method to decide when this level is done, signaling to the GameEngine that the next level should be loaded during the next tick.
		at the end of this method "completed = true" should be set if the necesarry checks are implemented.
		*/
		virtual void completeLevel() { }
		bool completed = false;

		/*
		data.
		*/
		std::vector<shared_ptr<Sprite>> sprites;
		std::vector<shared_ptr<Sprite>> added, removed;
		std::shared_ptr<SDL_Rect> playableArea;

	private:
		// A-grade things we did not have time to implement correctly {
		void runGravity();
		bool gravity;
		int gravityStrength;
		// }

		/*
		prepareNextTick:
		called by tick(), prepares things for the next tick, such as resetting states.
		*/
		void prepareNextTick(bool gameIsPaused);
	};
} //cwing