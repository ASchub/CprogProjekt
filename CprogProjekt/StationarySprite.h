#pragma once
#include <SDL.h>
#include "Sprite.h"

#include <string>
#include <memory>
/*
See "Sprite.h" for information about general variables and functions.
*/
namespace cwing {

	class StationarySprite : public Sprite
	{
	public:
		static shared_ptr<StationarySprite> getInstance(int x, int y, const char path[]);
		void draw() const;
	protected:
		StationarySprite(int x, int y, const char path[]);
	private:

	};

} //cwing