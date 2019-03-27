#pragma once
#include <SDL.h>

#include <memory>
#include <iostream>
#include <vector>

using namespace std;

namespace cwing {

	/*
	Virtual abstract class Sprite.
	*/
	class Sprite
	{
	public:
		virtual ~Sprite() { SDL_DestroyTexture(texture);};
		/*
		handleInput:
		Returns true if the game should be paused, takes an SDL_Event to evaluate and a bool gameIsPaused which will help it determine if it should act.
		Default implementation is that it does nothing and returns false.
		*/
		virtual bool handleInput(const SDL_Event& event, bool gameIsPaused) { return false; }

		/*
		resetMoveThisTick:
		Implemented in MovableSprite
		*/
		virtual void resetMoveThisTick() {}

		/*
		draw:
		virtual abstract method, all derived classes must implement this method, should implement methods for drawing the Sprite.
		*/
		virtual void draw() const = 0;

		/*
		deleting copy constructors to prevent errors.
		*/
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;

		/*
		handleCollision:
		virtual method. Implement this in subclass to allow responses to collisions with other Sprites.
		*/
		virtual void handleCollision(std::shared_ptr<SDL_Rect> intersection) {}

		/*
		getters/setters and state checking methods.
		*/
		shared_ptr<SDL_Rect> getRect() const { return rect; }
		bool isSolid() const { return solid; }
		void setSolid(bool isSolid) { solid = isSolid; }
		bool shouldBeDeleted() const { return toBeDeleted; };
		virtual void automaticBehaviour() {}
		// A-grade things we did not have time to implement correctly {
		void setBounces(int b) { bounces = b; }
		void setBounceRate(int b) { bounceRate = b; }
		bool isAffectedByGravity() { return affectedByGravity; }
		void setAffectedByGravity(bool isAffected) { affectedByGravity = isAffected; }
		void fall(int pixels);
		// }

		/*
		tick:
		This function handles all things a sprite should do each tick. It mostly calls other methods such as "handleCollision" and checks different states.
		*/
		int tick(std::vector<shared_ptr<Sprite>> sprites, std::shared_ptr<SDL_Rect> gameArea, bool gameIsPaused); //returns 0 if all went well.
		
	protected:
		/*
		constructor:
		Takes coordinates for placement, size of the sprite and a path to the media file, only supports .bmp files.
		*/
		Sprite(int x, int y, int w, int h, const char path[]); //konstrukorn, lär ta med dimensioner som argument, tar en path till en textur

		/*
		Help methods for collision detection
		*/
		bool checkSpriteCollision(shared_ptr<Sprite> other);
		bool checkBoundaryCollision(shared_ptr<SDL_Rect> playableArea);
		bool checkRectCollision(shared_ptr<SDL_Rect> otherRect, shared_ptr<SDL_Rect> intersectionResult);

		/*
		getters/setters and state checking methods.
		*/
		SDL_Texture* getTexture() const { return texture; }
		void setWH(int w, int h);
		void setXY(int x, int y);
		// when deleteMe is called, the Level where this sprite is placed will destroy it at the end of the current tick.
		void deleteMe() { toBeDeleted = true; }

		// A-grade things we did not have time to implement correctly {
		int bounces = 0; //default is that it doesnt apply
		int bounceRate = 0; //default is that it doesn't apply
		bool bouncing = false; //defalult is that it doesn't apply
		// }
	private:
		/*
		private variables & methods, mostly handling the SDL_Rect, the texture and the deletion of "this".
		*/
		shared_ptr<SDL_Rect> rect; //definitionen av en rektangel, som kommer innehålla våran sprite
		SDL_Texture* texture = nullptr;
		bool solid = true; //standard att sprites är solida
		void makeTexture(const char path[]);
		bool toBeDeleted = false;
		void adjustInsideWindow(shared_ptr<SDL_Rect> intersectionResult);

		// A-grade things we did not have time to implement correctly {
		bool affectedByGravity = false; //standard att sprites inte är påverkade av gravitationen
		// }
	};

} //cwing
