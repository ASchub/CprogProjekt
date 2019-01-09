#pragma once
#include <SDL.h>
#include "Sprite.h"

#include <string>
#include <memory>

namespace cwing {

	class StationarySprite : public Sprite
	{
	public:
		static shared_ptr<StationarySprite> getInstance(int x, int y, const char path[]); //only supports BMP paths atm.
		void draw() const;
		void handleCollision(const shared_ptr<Sprite> other) {}
	protected:
		StationarySprite(int x, int y, const char path[]);
	private:

	};

} //cwing