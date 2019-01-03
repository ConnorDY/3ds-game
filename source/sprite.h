#ifndef SPRITE_H
#define SPRITE_H

#include <citro2d.h>

class Sprite
{
	private:
		C2D_Sprite* spr;
		float x = 0, y = 0,
			  xScale = 1.f, yScale = 1.f,
			  centerX = 0, centerY = 0,
			  rot = 0;
	public:
		Sprite(C2D_SpriteSheet* spriteSheet, unsigned int num);
		~Sprite();

		C2D_Sprite* getSpr();

		void setPos(float xx, float yy);
		void setRot(float r);
		void setScale(float xs, float ys);
		void setCenter(float cx, float cy);
};

#endif
