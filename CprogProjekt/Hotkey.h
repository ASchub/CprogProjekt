#pragma once
#include <SDL.h>

namespace cwing {
	class Hotkey
	{
	public:
		virtual bool perform(bool gameIsPaused) { return changePauseUnpause; }
		SDL_Keycode getKey() const { return key; }
	protected:
		Hotkey(SDL_Keycode k, bool pauseGame = false, bool reactWhenGameIsPaused = false) { key = k; changePauseUnpause = pauseGame; reactWhenPaused = reactWhenGameIsPaused; }
		bool changePauseUnpause;
		bool reactWhenPaused;
	private:
		SDL_Keycode key;
	};
}


