#include "System.h"
#include <SDL.h>

#include <stdexcept>
#include <memory>

namespace cwing {

	/*
	Initializes window, renderer and font.
	*/
	cwing::System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("Cwing", 100, 100, 800, 600, 0);			// posX, posY, height, width, no flags
		ren = SDL_CreateRenderer(win, -1, 0);							//-1 means take first available renderer, no flags
		if (TTF_Init() == -1)											//checks if TTF has been successfully initialized
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}
		font = TTF_OpenFont("c:/Windows/Fonts/arial.ttf", 36);
		if (font == nullptr)											//checks if font has been successfully initialized
			throw std::runtime_error("Font not found");
	}

	SDL_Renderer *System::getRen() const {
		return ren;
	}

	TTF_Font* System::getFont() const {
		return font;
	}

	SDL_Window* System::getWin() const {
		return win;
	}

	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	/*
	Definition of the global sys object. Declared extern in the header file.
	*/
	System sys;

} //cwing