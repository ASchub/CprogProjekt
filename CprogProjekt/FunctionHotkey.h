#pragma once
#include <string>
#include <memory>
#include "Hotkey.h"
using namespace std;

namespace cwing {

	class FunctionHotkey : public Hotkey
	{
	public:
		bool perform(bool gameIsPaused) { if (!gameIsPaused || gameIsPaused && reactWhenPaused) { doIt(); } }
		static shared_ptr<FunctionHotkey> getInstance(SDL_Keycode k, void(*f)()) {
			return shared_ptr<FunctionHotkey>(new FunctionHotkey(k, f));
		}
	protected:
		FunctionHotkey(SDL_Keycode k, void(*f)()) : Hotkey(k), doIt(f){}
	private:
		void(*doIt)();
	};

} //cwing