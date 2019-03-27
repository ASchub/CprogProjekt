#pragma once

#include "Sprite.h"

#include <memory>
#include <string>

namespace cwing {

	class TextBox : public Sprite
	{
	public:
		static shared_ptr<TextBox> getInstance(int x, int y, const char path[]); // only supports bmpd
		void draw() const;
		bool handleInput(const SDL_Event& event, bool gameIsPaused);
		bool textInput(const SDL_Event& event);
		void backspace();
		bool mouseDown(const SDL_Event & event);
		bool keyDown(const SDL_Event & event);
		std::shared_ptr<std::string> getText() { return inputText; }
		~TextBox();
	protected:
		TextBox(int x, int y, const char path[]);
	private:
		bool loadTextureFromText(std::string text, SDL_Color color);
		void reRender();
		SDL_Color textColor = { 0,0,0,0xFF };
		SDL_Texture* inputTexture = NULL;
		std::shared_ptr<std::string> inputText;
		bool typing = false;
	};

}