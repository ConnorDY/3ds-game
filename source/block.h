#ifndef BLOCK_H
#define BLOCK_H

#include <citro2d.h>
#include "rect.h"

class Block
{
	private:
		float x, y, w, h;
		C2D_TextBuf textBuf;
		C2D_Text txt;
	public:
		Block(float xx, float yy, float ww, float hh, unsigned int id);

		Rect* getRect() const;
		void draw(float xOffset, float yOffset);
};

#endif
