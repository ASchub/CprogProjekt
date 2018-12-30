#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
using namespace std;
#define FPS 60

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	Mix_Chunk* muzak = Mix_LoadWAV("c:/sounds/bgMusic.wav");
	int volume = 64;
	Mix_Volume(-1, volume);
	int chNr = Mix_PlayChannel(-1, muzak, -1);
	Mix_Chunk* skott = Mix_LoadWAV("c:/sounds/klick.wav");
	bool paused = false;

	SDL_Window* win = SDL_CreateWindow("Window", 100, 100, 500, 600, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

	TTF_Font* font = TTF_OpenFont("c:/Windows/Fonts/arial.ttf", 36);

	SDL_Texture* bgTx = IMG_LoadTexture(ren, "c:/images/bg.bmp");

	SDL_Surface* gubbSurf = SDL_LoadBMP("c:/images/gubbe.bmp");
	Uint32 white = SDL_MapRGB(gubbSurf->format, 255, 255, 255);
	SDL_SetColorKey(gubbSurf, true, white);
	SDL_Texture* gubbTx = SDL_CreateTextureFromSurface(ren, gubbSurf);
	SDL_Rect gubbRect = { 0, 0, gubbSurf->w, gubbSurf->h };
	SDL_FreeSurface(gubbSurf);

	SDL_Surface* donkSurf = IMG_Load("c:/images/donkey.png");
	SDL_Texture* donkTx = SDL_CreateTextureFromSurface(ren, donkSurf);
	int w, h;
	SDL_QueryTexture(donkTx, NULL, NULL, &w, &h);
	SDL_Rect donkRect = { 0, 0, w, h };

	const int tickInterval = 1000 / FPS;

	bool moving = false;
	bool runOn = true;

	int varv = 0;
	while (runOn) {
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: runOn = false; break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP: gubbRect.y--; break;
				case SDLK_DOWN: gubbRect.y++; break;
				case SDLK_RIGHT: gubbRect.x++; break;
				case SDLK_LEFT: gubbRect.x--; break;
				case '+': Mix_Volume(chNr, ++volume); break;
				case '-': Mix_Volume(chNr, --volume); break;
				case 'p':
					if (paused)
						Mix_Resume(chNr);
					else
						Mix_Pause(chNr);
					paused = !paused;
				} // inre switch
				break;
			case SDL_MOUSEBUTTONDOWN: {
				Mix_PlayChannel(-1, skott, 0);
				SDL_Point point = { event.button.x, event.button.y };
				if (SDL_PointInRect(&point, &gubbRect))
					moving = true;
			}
			break;
			case SDL_MOUSEBUTTONUP:
				moving = false;
				break;
			case SDL_MOUSEMOTION:
				if (moving) {
					gubbRect.x += event.motion.xrel;
					gubbRect.y += event.motion.yrel;
				}
				break;
			}//switch

		} // inre while

		varv++;
		string varvString = to_string(varv);
		TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
		SDL_Surface* varvSurf = TTF_RenderText_Solid(font, varvString.c_str(),
		{ 255, 255, 255 });
		SDL_Texture* varvTx = SDL_CreateTextureFromSurface(ren, varvSurf);
		SDL_Rect varvRect = { 400, 500, varvSurf->w, varvSurf->h };
		SDL_FreeSurface(varvSurf);

		gubbRect.x++;

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, bgTx, NULL, NULL);
		SDL_RenderCopy(ren, gubbTx, NULL, &gubbRect);
		SDL_RenderCopy(ren, donkTx, NULL, &donkRect);
		SDL_RenderCopy(ren, varvTx, NULL, &varvRect);
		SDL_RenderPresent(ren);

		SDL_DestroyTexture(varvTx);

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	} // yttre while

	Mix_FreeChunk(muzak);
	Mix_FreeChunk(skott);
	SDL_DestroyTexture(donkTx);
	SDL_DestroyTexture(gubbTx);
	SDL_DestroyTexture(bgTx);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}