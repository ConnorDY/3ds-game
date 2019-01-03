#include "sprite.h"

Sprite::Sprite(C2D_SpriteSheet* spriteSheet, unsigned int num)
{
	spr = new C2D_Sprite();
	C2D_SpriteFromSheet(spr, *spriteSheet, num);
}

/* Accessors */
C2D_Sprite* Sprite::getSpr()
{
	return spr;
}

/* Setters */
void Sprite::setPos(float xx, float yy)
{
	x = xx;
	y = yy;
	C2D_SpriteSetPos(spr, x, y);
}

void Sprite::setRot(float r)
{
	rot = r;
	C2D_SpriteSetRotation(spr, rot);
}

void Sprite::setScale(float xs, float ys)
{
	xScale = xs;
	yScale = ys;
	C2D_SpriteSetScale(spr, xScale, yScale);
}

void Sprite::setCenter(float cx, float cy)
{
	centerX = cx;
	centerY = cy;
	C2D_SpriteSetCenter(spr, centerX, centerY);
}
