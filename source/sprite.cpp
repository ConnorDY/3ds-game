#include "sprite.h"

Sprite::Sprite(C2D_SpriteSheet* spriteSheet, unsigned int num)
{
	C2D_SpriteFromSheet(&spr, *spriteSheet, num);
}

/* Accessors */
C2D_Sprite* Sprite::getSpr()
{
	return &spr;
}

/* Setters */
void Sprite::setPos(float xx, float yy)
{
	x = xx;
	y = yy;
	C2D_SpriteSetPos(&spr, x, y);
}

void Sprite::setRot(float r)
{
	rot = r;
	C2D_SpriteSetRotation(&spr, rot);
}

void Sprite::setCenter(float xx, float yy)
{
	cx = xx;
	cy = yy;
	C2D_SpriteSetCenter(&spr, cx, cy);
}
