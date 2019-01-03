#pragma once
#include <SDL.h>
class Hotkey
{
public:
	virtual void perform() {}
	~Hotkey();
	SDL_Keycode getKey() const { return key; }
protected:
	Hotkey(SDL_Keycode k);
private:
	SDL_Keycode key;
};

