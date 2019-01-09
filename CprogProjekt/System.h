#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
/*
Globalt system objekt, där vi lägger in globala variabler som tex vår renderare.
*/

namespace cwing {

	using namespace std;

	class System
	{
	public:
		System();
		SDL_Renderer *getRen() const;
		TTF_Font* getFont() const;
		~System();
	private:
		SDL_Window *win;
		SDL_Renderer *ren;
		TTF_Font* font;
	};
	
	extern System sys; //extern deklarering visar allt som läser denna att det finns ett objekt "sys" nånstans, men den defineras inte här.
	extern Uint32 BASE_SPEED;
	extern Uint32 BASE_GRAVITY;

} //cwing