#pragma once
#include "Hotkey.h"

namespace cwing {

	class FunctionHotkey : public Hotkey
	{
	public:
		void perform() { doIt(); }
		static Hotkey* getInstance(SDL_Keycode k, void(*f)());
	protected:
		FunctionHotkey(SDL_Keycode k, void(*f)());
	private:
		void(*doIt)();
	};

} //cwing