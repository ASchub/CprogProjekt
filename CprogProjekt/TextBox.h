#pragma once

#include "Sprite.h"

#include <memory>
#include <string>
/*
See "Sprite.h" for information about general variables and functions.
*/
namespace cwing {

	class TextBox : public Sprite
	{
	public:
		static shared_ptr<TextBox> getInstance(int x, int y, const char path[]); // only supports bmpd
		~TextBox();
		void draw() const;

		/* 
		handleInput:
		Pauses the game if you click inside the TextBox, and allows you to type.
		Pressing RETURN will unpause the game and turn of typing to the TextBox.
		*/
		bool handleInput(const SDL_Event& event, bool gameIsPaused);

		/*
		help functions for handling typing into the TextBox.
		*/
		bool textInput(const SDL_Event& event);
		void backspace();
		bool mouseDown(const SDL_Event & event);
		bool keyDown(const SDL_Event & event);

		/*
		getters and setters
		*/
		std::shared_ptr<std::string> getText() { return inputText; }
		
	protected:
		TextBox(int x, int y, const char path[]);
	private:
		/*
		reRender and loadTextureFromText:
		renders the graphics again if more things are typed while the textbox is active.
		*/
		void reRender();
		bool loadTextureFromText(std::string text, SDL_Color color);
		
		SDL_Color textColor = { 0,0,0,0xFF };
		SDL_Texture* inputTexture = NULL;
		std::shared_ptr<std::string> inputText;
		bool typing = false;
	};

}