#include "block.h"

#include <string>
#include "globals.h"

Block::Block(float xx, float yy, float ww, float hh, unsigned int id)
{
	x = xx;
	y = yy;
	w = ww;
	h = hh;

	textBuf = C2D_TextBufNew(32);
	C2D_TextParse(&txt, textBuf, std::to_string(id).c_str());
	C2D_TextOptimize(&txt);
}

void Block::draw(float xOffset, float yOffset)
{
	C2D_DrawRectSolid(x - xOffset, y - yOffset, 0, w, h, C2D_Color32(0x00, 0x00, 0xFF, 0x7F));

	#ifdef DEBUG_MODE
	C2D_DrawText(&txt, 0, x - xOffset, y - yOffset, .5f, .5f, .5f);
	#endif
}
