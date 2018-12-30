#include "Session.h"
#include <SDL.h>
#include "System.h"
using namespace std;
namespace cwing {

	Session::Session()
	{
	}

	void Session::add(Component* c) {
		added.push_back(c);
	}

	void Session::remove(Component *c) {
		removed.push_back(c);
	}

	void Session::run() {
		SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
		bool quit = false;

		while (!quit) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT: quit = true; break;
				case SDL_MOUSEBUTTONDOWN:
					for (Component* c : comps)
						c->mouseDown(event);
					break;
				case SDL_MOUSEBUTTONUP:
					for (Component* c : comps)
						c->mouseUp(event);
					break;
				case SDL_KEYDOWN:
					for (Component* c : comps)
						c->keyDown(event);
					break;
				case SDL_KEYUP:
					for (Component* c : comps)
						c->keyUp(event);
					break;
				}
			} // inre while

			for (Component* c : added)
				comps.push_back(c);
			added.clear();

			for (Component* c : removed) {
				for (vector<Component*>::iterator i = comps.begin(); i != comps.end(); )
					if (*i == c) {
						i = comps.erase(i);
						delete c;
					}
					else
						i++;
			}
			removed.clear();


			SDL_RenderClear(sys.getRen());
			for (Component* c : comps)
				c->draw();
			SDL_RenderPresent(sys.getRen());

		} // yttre while

	}

	Session::~Session()
	{
		for (Component* c : comps)
			delete c;
	}
} // cwing