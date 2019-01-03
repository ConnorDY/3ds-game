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
		unsigned int skin;
		float frameTimer = 0, x, y;
		C2D_SpriteSheet* spriteSheet;
	public:
		Player(C2D_SpriteSheet* sS, unsigned int skin);
		~Player();

		unsigned int getSkin();

		void setPos(float xx, float yy);
		void setSkin(unsigned int s);
		void moveRight();
		void moveLeft();
		void draw();
};

#endif
