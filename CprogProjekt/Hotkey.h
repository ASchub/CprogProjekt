#pragma once
#include <SDL.h>

class Hotkey
{
public:
	virtual void perform() {}
	SDL_Keycode getKey() const { return key; }
protected:
	Hotkey(SDL_Keycode k) { key = k; }
private:
	SDL_Keycode key;
};

