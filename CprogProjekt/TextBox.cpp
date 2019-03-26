#include "TextBox.h"
#include "System.h"

#include <memory>

using namespace std;

namespace cwing {

	shared_ptr<TextBox> TextBox::getInstance(int x, int y, const char path[]) {
		return shared_ptr<TextBox>(new TextBox(x, y, path));
	}

	TextBox::TextBox(int x, int y, const char path[]) : Sprite(x, y, 0, 0, path) 
	{
		textColor->r = 0;
		textColor->g = 0;
		textColor->b = 0;
		textColor->a = 0xFF;

		SDL_SetTextInputRect(getRect().get());
	}

	TextBox::~TextBox() {
		delete textColor;
		delete inputText;
		delete text;
		delete composition;
		delete cursor;
		delete selection_len;
	}

	void TextBox::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, getRect().get());
	}

	void TextBox::textInput(SDL_Event& event) {
		strcat(text, event.text.text);
	}

	void TextBox::textEdit(SDL_Event& event) {
		composition = event.edit.text;
		cursor = &(event.edit.start);
		selection_len = &(event.edit.length);
	}


} //cwing