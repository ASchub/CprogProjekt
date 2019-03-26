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
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}

		inputText = std::shared_ptr<std::string>(new string());
		if (inputTexture != nullptr)
			SDL_DestroyTexture(inputTexture);

		SDL_Surface* surf = SDL_LoadBMP(path);
		if (!loadTextureFromText("Enter name here", textColor))
		{
			printf("Failed to render text texture!\n");
		}

		setWH(surf->w, surf->h);
		SDL_FreeSurface(surf);

		SDL_SetTextInputRect(getRect().get());
	}

	TextBox::~TextBox() {
		SDL_DestroyTexture(inputTexture);
	}

	void TextBox::draw() const {
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, getRect().get());
		SDL_RenderCopy(sys.getRen(), inputTexture, NULL, getRect().get());
	}

	void TextBox::reRender() {
		if (inputText->length() > 0)
		{
			loadTextureFromText(inputText->c_str(), textColor);
		}
		//Text is empty
		else
		{
			loadTextureFromText(" ", textColor);
		}
	}

	bool TextBox::loadTextureFromText(std::string text, SDL_Color color)
	{
		//Get rid of preexisting texture
		if (inputTexture != nullptr) {
			SDL_DestroyTexture(inputTexture);
		}
		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(sys.getFont(), text.c_str(), color);
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			//Create texture from surface pixels
			inputTexture = SDL_CreateTextureFromSurface(sys.getRen(), textSurface);
			if (inputTexture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				setWH(textSurface->w, textSurface->h);
				//Get image dimensions
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}

		//Return success
		return inputTexture != NULL;
	}

	void TextBox::textInput(SDL_Event& event) {
		if (event.key.keysym.sym != SDLK_BACKSPACE) {
			inputText->append(event.text.text);
		}
		reRender();
	}

	void TextBox::backspace() {
		if (inputText->length() > 0) {
			inputText->pop_back();
		}
		reRender();
	}


} //cwing