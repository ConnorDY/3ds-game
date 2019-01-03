#include "rect.h"

Rect::Rect(float xx, float yy, float ww, float hh)
{
	x = xx;
	y = yy;
	w = ww;
	h = hh;
}

float Rect::getX()
{
	return x;
}

float Rect::getY()
{
	return y;
}

float Rect::getW()
{
	return w;
}

float Rect::getH()
{
	return h;
}

bool Rect::intersects(Rect* r)
{
	float right = x + w;
	float bottom = y + h;
	float otherRight = r->getX() + r->getW();
	float otherBottom = r->getY() + r->getH();

	return (x < otherRight && right > r->getX() &&
			y < otherBottom && bottom > r->getY());
}
