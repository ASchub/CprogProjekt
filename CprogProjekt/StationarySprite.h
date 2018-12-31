#pragma once
#include <SDL.h>
#include "Sprite.h"
#include <string>

namespace cwing {

	class StationarySprite : public Sprite
	{
	public:
		static StationarySprite* getInstance(int x, int y, const char path[]); //only supports BMP paths atm.
		void draw() const;
		~StationarySprite();
	protected:
		StationarySprite(int x, int y, const char path[]);
	private:

	};

} //cwing