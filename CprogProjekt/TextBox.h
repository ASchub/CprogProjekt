#pragma once

#include "Sprite.h"

#include <memory>
#include <string>

namespace cwing {

	class TextBox : public Sprite
	{
	public:
		static shared_ptr<TextBox> getInstance(int x, int y, const char path[]); // only supports bmp
		void draw() const;
		void textInput(SDL_Event& event);
		void textEdit(SDL_Event& event);
	protected:
		TextBox(int x, int y, const char path[]);
	private:
		SDL_Color* textColor;
		std::string* inputText;
		char* text;
		char* composition;
		Sint32* cursor;
		Sint32* selection_len;
	};

}