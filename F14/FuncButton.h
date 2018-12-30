#ifndef FUNCBUTTON_H
#define FUNCBUTTON_H
#include <string>
#include "Button.h"

namespace cwing {

	class FuncButton : public Button
	{
	public:
		static Button* getInstance(int x, int y, const std::string& txt,
			void(*f)(const std::string&)) {
			return new FuncButton(x, y, txt, f);
		}
		void perform(const std::string& txt) {
			doIt(txt);
		}
		
	protected:
		FuncButton(int x, int y, const std::string& txt,
			void(*f)(const std::string&)) :Button(x, y, txt), doIt(f) {}
	private:
		void(*doIt)(const std::string&);
	};

}
#endif