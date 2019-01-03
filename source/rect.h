#ifndef RECT_H
#define RECT_H

class Rect
{
	private:
		float x, y, w, h;
	public:
		Rect(float xx, float yy, float ww, float hh);
		
		float getX();
		float getY();
		float getW();
		float getH();
		bool intersects(Rect* r);
};

#endif
