#pragma once
#include <SDL.h>

#include <memory>
#include <iostream>
#include <vector>

using namespace std;

namespace cwing {

	class Sprite
	{
	public:
		virtual ~Sprite() { SDL_DestroyTexture(texture);};
		//då denna är för subklasserna, dvs virtual, ej abstrakt (=0) men vi deklarerar en tom metod för de subklasser som inte vill ha en
		//virtual void handleCollision(shared_ptr<const Sprite> other) {}
		virtual void mouseDown(const SDL_Event& event) {}
		virtual void mouseUp(const SDL_Event& event) {}
		//virtual void keyDown(const SDL_Event& event) {}
		//virtual void keyUp(const SDL_Event& event) {}
		virtual void resetMoveThisTick() {}
		shared_ptr<SDL_Rect> getRect() const { return rect; }
		virtual void draw() const = 0; //helt virtuel och abstrakt, alla objekt måste ritas ut så kan inte göra tom deklaration (=0)
		Sprite(const Sprite&) = delete; //Copy konstruktorn, ska ej finnas då vi inte vill kunna skapa objekt av denna abstrakta klass
		const Sprite& operator=(const Sprite&) = delete; //samma som ovan, ingen operator överlagring
		virtual void handleCollision(std::shared_ptr<SDL_Rect> intersection) {}
		bool isSolid() { return solid; }
		void setSolid(bool isSolid) { solid = isSolid; }

		//void checkCollideWithWindow();
		virtual int tick(std::vector<shared_ptr<Sprite>> sprites, std::shared_ptr<SDL_Rect> gameArea) {
			//checkCollideWithWindow();
			checkBoundaryCollision(gameArea);
			for (shared_ptr<Sprite> s : sprites) {
				if (this != s.get()) {
					checkSpriteCollision(s);
					//checkCollision(s);
				}
				draw();
			}
			return 0;
		} //returns 0 if all went well.

		//elasticity
		void setBounces(int b) { bounces = b; }
		void setBounceRate(int b) { bounceRate = b; }

		//gravity stuff
		bool isAffectedByGravity() { return affectedByGravity; }
		void setAffectedByGravity(bool isAffected) { affectedByGravity = isAffected; } //möjlighet att välja om sprite skall påverkas eller ej1
		void fall(int pixels);
		
	protected:
		SDL_Texture* getTexture() const { return texture; }
		Sprite(int x, int y, int w, int h, const char path[]); //konstrukorn, lär ta med dimensioner som argument, tar en path till en textur
		void setWH(int w, int h); //bör kunna ändra storlek/position för spriten
		void setXY(int x, int y);

		//virtual void handleCollision(shared_ptr<const Sprite> other) { }
		//bool checkCollision(shared_ptr<const Sprite> other); //returns 0 if no collision, 1-4 is the different directions where it colided

		//kollisionshantering, förenklad
		bool checkSpriteCollision(shared_ptr<Sprite> other);
		bool checkBoundaryCollision(shared_ptr<SDL_Rect> playableArea);
		bool checkRectCollision(shared_ptr<SDL_Rect> otherRect, shared_ptr<SDL_Rect> intersectionResult);


		//elasticity
		int bounces = 0; //default is that it doesnt apply
		int bounceRate = 0; //default is that it doesn't apply
		bool bouncing = false; //defalult is that it doesn't apply
	private:
		shared_ptr<SDL_Rect> rect; //definitionen av en rektangel, som kommer innehålla våran sprite
		SDL_Texture* texture = nullptr;
		bool solid = true; //standard att sprites är solida
		void makeTexture(const char path[]);

		//gravity stuff
		bool affectedByGravity = false; //standard att sprites inte är påverkade av gravitationen
		void adjustInsideWindow(shared_ptr<SDL_Rect> intersectionResult);
	};

} //cwing
