#pragma once
#include <SDL.h>

namespace cwing {

	class Sprite
	{
	public:
		virtual ~Sprite() { SDL_DestroyTexture(texture); };
		//då denna är för subklasserna, dvs virtual, ej abstrakt (=0) men vi deklarerar en tom metod för de subklasser som inte vill ha en
		virtual void mouseDown(const SDL_Event& event) {}
		virtual void mouseUp(const SDL_Event& event) {}
		virtual void keyDown(const SDL_Event& event) {}
		virtual void keyUp(const SDL_Event& event) {}
		SDL_Rect getRect() const { return rect; }
		virtual void draw() const = 0; //helt virtuel och abstrakt, alla objekt måste ritas ut så kan inte göra tom deklaration (=0)
		Sprite(const Sprite&) = delete; //Copy konstruktorn, ska ej finnas då vi inte vill kunna skapa objekt av denna abstrakta klass
		const Sprite& operator=(const Sprite&) = delete; //samma som ovan, ingen operator överlagring
	protected:
		SDL_Texture* getTexture() const { return texture; }
		Sprite(int x, int y, int w, int h, const char path[] = "../media/gubbe.bmp"); //konstrukorn, lär ta med dimensioner som argument, tar en path till en textur
		void setWH(int w, int h); //bör kunna ändra storlek/position för spriten
		void setXY(int x, int y);
	private:
		SDL_Rect rect; //definitionen av en rektangel, som kommer innehålla våran sprite
		SDL_Texture* texture = nullptr;
		void makeTexture(const char path[]);
	};

} //cwing
