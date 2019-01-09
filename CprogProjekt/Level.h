#pragma once
#include "Sprite.h"
#include "Hotkey.h"

#include <vector>
#include <memory>

using namespace std;

namespace cwing {
	class Level
	{
	public:
		~Level(); //Destruktor
		static shared_ptr<Level> getInstance(bool gravity, int downwardsMotion);
		static shared_ptr<Level> getInstance();
		void add(shared_ptr<Sprite> s);
		void remove(shared_ptr<Sprite> s);
		void tick();
		Level(const Level&) = delete; //Copy-konstruktorn, skall inte finnas pga värdesemantik
		const Level& operator=(const Sprite&) = delete; //ingen operatoröverlagring

		//gravity stuff
		void setGravity(bool g, int downwardsMotion);
		bool getGravity() { return &gravity; }

	protected:
		Level(bool gravityOn, int downwardsMotion); //Konstruktor

	private:
		std::vector<shared_ptr<Sprite>> sprites;
		std::vector<shared_ptr<Sprite>> added, removed;

		//gravity stuff
		void runGravity();
		void prepareNextTick();
		bool gravity;
		int gravityStrength;

	};
} //cwing