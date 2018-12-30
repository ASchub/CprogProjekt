#include "System.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdexcept>
using namespace std;

namespace cwing {

	System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("Cwing", 100, 100, 800, 600, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();
		font = TTF_OpenFont("c:/Windows/Fonts/arial.ttf", 36);
		if (font == nullptr)
			throw std::runtime_error("Font ej hittad!");

		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_Chunk* m = Mix_LoadWAV("c:/sounds/bgMusic.wav");
		Mix_PlayChannel(-1, m, -1);
	}

	SDL_Renderer* System::getRen() const {
		return ren;
	}

	TTF_Font* System::getFont() const {
		return font;
	}

	System::~System()
	{
		Mix_CloseAudio();
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	System sys;

} // cwing