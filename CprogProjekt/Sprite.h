#pragma once
#include <SDL.h>

namespace cwing {

	class Sprite
	{
	public:
		virtual ~Sprite() {};
		//d� denna �r f�r subklasserna, dvs virtual, ej abstrakt (=0) men vi deklarerar en tom metod f�r de subklasser som inte vill ha en
		virtual void mouseDown(const SDL_Event& event) {}
		virtual void mouseUp(const SDL_Event& event) {}
		virtual void keyDown(const SDL_Event& event) {}
		virtual void keyUp(const SDL_Event& event) {}
		SDL_Rect getRect() const { return rect; }
		virtual void draw() const = 0; //helt virtuel och abstrakt, alla objekt m�ste ritas ut s� kan inte g�ra tom deklaration (=0)
		Sprite(const Sprite&) = delete; //Copy konstruktorn, ska ej finnas d� vi inte vill kunna skapa objekt av denna abstrakta klass
		const Sprite& operator=(const Sprite&) = delete; //samma som ovan, ingen operator �verlagring
	protected:
		Sprite(int x, int y, int w, int h); //konstrukorn, l�r ta med dimensioner som argument.
		void setWH(int w, int h); //b�r kunna �ndra storlek/position f�r spriten
		void setXY(int x, int y);
	private:
		SDL_Rect rect; //definitionen av en rektangel, som kommer inneh�lla v�ran sprite
	};

} //cwing
