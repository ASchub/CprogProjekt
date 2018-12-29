#pragma once
#include <string> //anv�nd EJ using namespace i header filer... d� �ppnas hela bibloteket f�r klasser som inkluderar denna.
#include <SDL.h>
#include "Sprite.h"

namespace cwing {
	class Labeled : public Sprite //subklass av sprite
	{
	public:
		void setText(const std::string & txt);
		std::string getText() const;
		//implementerar ej draw funktionen d� den g�rs annorlunda f�r olika Labeled klasser, detta g�r att vi inte kan skapa objekt av denna klass d� "draw" �r abstrakt.
		~Labeled();
	protected:
		Labeled(int x, int y, const std::string& txt); //s� vi kan skapa subklasser, och ej deklarera objekt. avg�r h,w med textens l�ngd.
		SDL_Texture* getTexture() const { return texture; }
	private:
		std::string text;
		SDL_Texture* texture = nullptr;
		void makeTexture();
	};


} //cwing