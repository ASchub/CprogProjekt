#pragma once
#include <string>
#include <memory>
#include "Hotkey.h"
using namespace std;

namespace cwing {

	class FunctionHotkey : public Hotkey
	{
	public:
		void perform() { doIt(); }
		static shared_ptr<FunctionHotkey> getInstance(SDL_Keycode k, void(*f)());
	protected:
		FunctionHotkey(SDL_Keycode k, void(*f)());
	private:
		void(*doIt)();
	};

} //cwing