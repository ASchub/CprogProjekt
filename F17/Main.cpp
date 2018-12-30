#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

void showPixel(int x, int y, SDL_Surface* surface) {
	cout << x << ", " << y << endl;
	if (x < surface->w && y < surface->h) {
		SDL_LockSurface(surface);
		Uint32* pixels = static_cast<Uint32*>(surface->pixels);
		Uint32 pixel = pixels[y*surface->w + x];
		SDL_UnlockSurface(surface);
		Uint32 red = pixel & surface->format->Rmask;
		red = red >> surface->format->Rshift;
		Uint32 green = pixel & surface->format->Gmask;
		green = green >> surface->format->Gshift;
		Uint32 blue = pixel & surface->format->Bmask;
		blue = blue >> surface->format->Bshift;
		Uint32 alpha = pixel & surface->format->Amask;
		alpha = alpha >> surface->format->Ashift;
		cout << "r=" << red << " g=" << green << " b=" << blue << " a=" << alpha << endl;
	}
}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win = SDL_CreateWindow("Donkey", 800, 200, 400, 400, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	SDL_Surface* surface = IMG_Load("c:/images/donkey.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);

	bool goOn = true;
	while (goOn) {
		SDL_Event eve;
		while (SDL_PollEvent(&eve)) {
			switch (eve.type) {
			case SDL_QUIT: goOn = false; break;
			case SDL_MOUSEBUTTONDOWN:
				showPixel(eve.button.x, eve.button.y, surface);
			} // switch
		} // inre while

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderClear(ren);
		SDL_Rect dest = { 0, 0, surface->w, surface->h };
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
		SDL_RenderDrawRect(ren, &dest);
		SDL_RenderCopy(ren, texture, NULL, &dest);
		SDL_RenderPresent(ren);

	} // yttre while

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}