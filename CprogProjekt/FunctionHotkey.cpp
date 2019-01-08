#include "FunctionHotkey.h"

namespace cwing {

	Hotkey* FunctionHotkey::getInstance(SDL_Keycode k, void(*f)()) {
		return new FunctionHotkey(k, f);
	}

	FunctionHotkey::FunctionHotkey(SDL_Keycode k, void(*f)()) : Hotkey(k), doIt(f)
	{
	}

} //cwing