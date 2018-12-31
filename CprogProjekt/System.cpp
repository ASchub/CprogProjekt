#include "System.h"
#include <SDL.h>
#include <stdexcept>

namespace cwing {

	cwing::System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		//bygger fönstret och renderaren för vårat globala sys objekt.
		win = SDL_CreateWindow("Cwing", 100, 100, 800, 600, 0); //posX,posY,höjd,bredd,inga flaggor
		ren = SDL_CreateRenderer(win, -1, 0); //-1 betyder ta första bästa renderare, inga flaggor
		TTF_Init();
		font = TTF_OpenFont("c:/Windows/Fonts/arial.ttf", 36);
		if (font == nullptr)
			throw std::runtime_error("Font not found");
	}

	SDL_Renderer *System::getRen() const {
		return ren;
	}

	TTF_Font* System::getFont() const {
		return font;
	}

	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	System sys; //definerar ett objekt, globalt så deklareras som extern i header filen

} //cwing