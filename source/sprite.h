#ifndef SPRITE_H
#define SPRITE_H

#include <citro2d.h>

class Sprite
{
	private:
		C2D_Sprite spr;
		float x = 0, y = 0, cx = 0, cy = 0, rot = 0;
	public:
		Sprite(C2D_SpriteSheet spriteSheet, unsigned int num);
		C2D_Sprite* getSpr();

		void setPos(float xx, float yy);
		void setRot(float r);
		void setCenter(float xx, float yy);
};

#endif
