#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
/*
Global System object, containing global variables: the renderer, window and font
*/

namespace cwing {

	using namespace std;

	class System
	{
	public:
		/*
		Constructor
		*/
		System();

		/*
		Getters
		*/
		SDL_Renderer *getRen() const;
		TTF_Font* getFont() const;
		SDL_Window* getWin() const;
		
		/*
		Destructor
		*/
		~System();
	private:
		/*
		Private variables
		*/
		SDL_Window *win;
		SDL_Renderer *ren;
		TTF_Font* font;
	};
	
	/*
	Extern declaration of the system object gives the entire program access to the object "sys".
	OBS! The object is not defined here.
	*/
	extern System sys;

} //cwing