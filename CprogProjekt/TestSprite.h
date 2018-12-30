#pragma once
#include <SDL.h>
#include "Sprite.h"
#include <string>

namespace cwing {

	class TestSprite : public Sprite
	{
	public:
		static TestSprite* getInstance(int x, int y, const char path[]); //only supports BMP paths atm.
		void draw() const;
		~TestSprite();
	protected:
		TestSprite(int x, int y, const char path[]);
		SDL_Texture* getTexture() const { return texture; }
	private:
		SDL_Texture* texture = nullptr;
		void makeTexture(const char path[]);

	};

} //cwing