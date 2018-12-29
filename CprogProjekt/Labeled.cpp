#include "Labeled.h"
#include "SDL_ttf.h"
#include "System.h"

using namespace std;

namespace cwing {

	Labeled::Labeled(int x, int y, const string& txt) :Sprite(x, y, 0, 0), text(txt)
	{
		makeTexture();
	}

	string Labeled::getText() const {
		return text;
	}

	//denna funktion kanske bör returnera texturen istället
	void Labeled::makeTexture() {
		if (texture != nullptr) //om den redan initieras måste vi städa bort den gamla texturen
			SDL_DestroyTexture(texture);
		//borde kanske kasta undantag om surf=null
		SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), text.c_str(), { 0,0,0 }); //oflexibel, vi bestämmer font storlek i System och färgen i koden... bör ändras
		texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
		setWH(surf->w, surf->h);
		SDL_FreeSurface(surf);
	}

	void Labeled::setText(const string& txt) {
		text = txt;
		makeTexture();
	}

	Labeled::~Labeled()
	{
		SDL_DestroyTexture(texture);
	}

}
