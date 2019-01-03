#ifndef RECT_H
#define RECT_H

class Rect
{
	private:
		float x, y, w, h;
	public:
		Rect(float xx, float yy, float ww, float hh);
		
		float getX() const;
		float getY() const;
		float getW() const;
		float getH() const;
		bool intersects(Rect* r) const;
};

#endif
