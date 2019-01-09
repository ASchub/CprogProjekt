#include "FunctionHotkey.h"
#include <memory>
using namespace std;

namespace cwing {

	shared_ptr<FunctionHotkey> FunctionHotkey::getInstance(SDL_Keycode k, void(*f)()) {
		return shared_ptr<FunctionHotkey>(new FunctionHotkey(k, f));
	}

	FunctionHotkey::FunctionHotkey(SDL_Keycode k, void(*f)()) : Hotkey(k), doIt(f)
	{
	}

} //cwing