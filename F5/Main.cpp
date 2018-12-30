#include <SDL.h>

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* win = SDL_CreateWindow("Window", 100, 100, 500, 600, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

	SDL_Surface* bgSurf = SDL_LoadBMP("c:/images/bg.bmp");
	SDL_Texture* bgTx = SDL_CreateTextureFromSurface(ren, bgSurf);
	SDL_FreeSurface(bgSurf);

	SDL_Surface* gubbSurf = SDL_LoadBMP("c:/images/gubbe.bmp");
	Uint32 white = SDL_MapRGB(gubbSurf->format, 255, 255, 255);
	SDL_SetColorKey(gubbSurf, true, white);
	SDL_Texture* gubbTx = SDL_CreateTextureFromSurface(ren, gubbSurf);
	SDL_Rect gubbRect = { 0, 0, gubbSurf->w, gubbSurf->h };
	SDL_FreeSurface(gubbSurf);

	bool moving = false;
	bool runOn = true;
	while (runOn) {
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
				} // inre switch
				break;
			case SDL_MOUSEBUTTONDOWN: {
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

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, bgTx, NULL, NULL);
		SDL_RenderCopy(ren, gubbTx, NULL, &gubbRect);
		SDL_RenderPresent(ren);
	} // yttre while

	SDL_DestroyTexture(bgTx);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}