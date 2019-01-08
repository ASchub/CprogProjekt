#pragma once
#include "Hotkey.h"

namespace cwing {

	template <typename T>
	class MemberHotkey : public Hotkey
	{
	public:
		T* getObject() { return object; }
		void perform() { (object->*doIt)(); } //might need parameter "(Hotkey* source)" which would need extra handling
		static Hotkey* getInstance(SDL_Keycode k, T* obj, void (T::*f)()) {
			return new MemberHotkey<T>(k, obj, f);
		}
	protected:
		MemberHotkey(SDL_Keycode k, T* obj, void (T::*f)()) : Hotkey(k), object(obj), doIt(f) {}
	private:
		T* object;
		void (T::*doIt)();
	};

} //cwing