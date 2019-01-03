#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <citro2d.h>
#include "globals.h"
#include "sprite.h"

class Player
{
	private: 
		std::vector<Sprite*> sprites;
		std::vector<unsigned int> anim {0, 1, 0, 2};
		float frameTimer = 0, x, y;
	public:
		Player(C2D_SpriteSheet spriteSheet, unsigned int skin);
		~Player();

		void setPos(float xx, float yy);
		void moveRight();
		void moveLeft();
		void draw();
};

#endif
