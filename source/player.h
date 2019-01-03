#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <citro2d.h>
#include "globals.h"
#include "sprite.h"
#include "block.h"

class Room;

class Player
{
	private: 
		std::vector<Sprite*> sprites;
		std::vector<unsigned int> anim {0, 1, 0, 2};
		unsigned int skin;
		float frameTimer = 0,
			  x = SCREEN_WIDTH / 2.f,
			  y = (SCREEN_HEIGHT / 2.f) + 32,
			  xLast = x, yLast = y,
			  dx = 0.f, dy = 0.f,
			  xScale = 1.f, yScale = 1.f,
			  gravity = .5f, maxFallSpeed = 4.f;
		C2D_SpriteSheet* spriteSheet;
		Room* level;
	public:
		Player(C2D_SpriteSheet* sS, unsigned int skin, Room* r);
		~Player();

		float getX();
		float getY();
		unsigned int getSkin();
		std::vector<Block*> allCollisions(float xx, float yy) const;
		bool placeFree(float xx, float yy) const;

		void setPos(float xx, float yy, float offsetX, float offsetY);
		void setOffset(float offsetX, float offsetY);
		void setScale(float xs, float ys);
		void setSkin(unsigned int s);

		void moveRight();
		void moveLeft();
		void jump();

		void applyGravityOnce();
		void applyVelocityOnce();
		void loopAroundMap();
		void pushOutOfSolids();

		void draw();
};

#endif
