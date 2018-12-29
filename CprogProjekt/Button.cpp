#include "Button.h"
#include <SDL_image.h>
#include "System.h"
using namespace std;

namespace cwing {

	Button* Button::getInstance(int x, int y, const string& txt) {
		return new Button(x, y, txt);
	}

	Button::Button(int x, int y, const string& txt) :Labeled(x, y, txt)
	{
		upIcon = IMG_LoadTexture(sys.getRen(), "f:/images/knapp.png");
		downIcon = IMG_LoadTexture(sys.getRen(), "f:/images/knapp.png");
	}

	void Button::mouseDown(const SDL_Event& event) {
		SDL_Point p = { event.button.x, event.button.y };
		if (SDL_PointInRect(&p, &getRect()))
			isDown = true;
	}

	void Button::mouseUp(const SDL_Event& event) {
		SDL_Point p = { event.button.x, event.button.y };
		if (SDL_PointInRect(&p, &getRect()))
			perform(getText());
		isDown = false;
	}

	void Button::draw() const {
		if (isDown)
			SDL_RenderCopy(sys.getRen(), downIcon, NULL, &getRect());
		else
			SDL_RenderCopy(sys.getRen(), upIcon, NULL, &getRect());
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &getRect());
	}

	Button::~Button()
	{
		SDL_DestroyTexture(upIcon);
		SDL_DestroyTexture(downIcon);
	}

}