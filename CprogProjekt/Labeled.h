#pragma once
#include <string> //använd EJ using namespace i header filer... då öppnas hela bibloteket för klasser som inkluderar denna.
#include <SDL.h>
#include "Sprite.h"

namespace cwing {
	class Labeled : public Sprite //subklass av sprite
	{
	public:
		void setText(const std::string & txt);
		std::string getText() const;
		//implementerar ej draw funktionen då den görs annorlunda för olika Labeled klasser, detta gör att vi inte kan skapa objekt av denna klass då "draw" är abstrakt.
		~Labeled();
	protected:
		Labeled(int x, int y, const std::string& txt); //så vi kan skapa subklasser, och ej deklarera objekt. avgör h,w med textens längd.
		SDL_Texture* getTexture() const { return texture; }
	private:
		std::string text;
		SDL_Texture* texture = nullptr;
		void makeTexture();
	};


} //cwing