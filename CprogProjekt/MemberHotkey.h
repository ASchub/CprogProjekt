#pragma once
#include "Hotkey.h"
#include <memory>

namespace cwing {

	template <typename T>
	class MemberHotkey : public Hotkey
	{
	public:
		T* getObject() { return object; }
		void perform() { (object.get()->*doIt)(); } //might need parameter "(Hotkey* source)" which would need extra handling
		static std::shared_ptr<MemberHotkey> getInstance(SDL_Keycode k, std::shared_ptr<T> obj, void (T::*f)()) {
			return std::shared_ptr<MemberHotkey>(new MemberHotkey<T>(k, obj, f));
		}
	protected:
		MemberHotkey(SDL_Keycode k, std::shared_ptr<T> obj, void (T::*f)()) : Hotkey(k), object(obj), doIt(f) {}
	private:
		shared_ptr<T> object;
		void (T::*doIt)();
	};

} //cwing