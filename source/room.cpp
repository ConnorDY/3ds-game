#include "room.h"

Room::Room()
{
	// Load sprite sheets
	C2D_SpriteSheet playerSheet = C2D_SpriteSheetLoad("romfs:/gfx/player.t3x");
	C2D_SpriteSheet mapSheetBG = C2D_SpriteSheetLoad("romfs:/gfx/map1bg.t3x");
	C2D_SpriteSheet mapSheetFG = C2D_SpriteSheetLoad("romfs:/gfx/map1fg.t3x");

	if (!playerSheet || !mapSheetBG || !mapSheetFG) svcBreak(USERBREAK_PANIC);

	spriteSheets["player"] = playerSheet;
	spriteSheets["map1bg"] = mapSheetBG;
	spriteSheets["map1fg"] = mapSheetFG;

	// Initialize sprites
	plyr = new Player(&spriteSheets["player"], 0);
	bg = new Sprite(&spriteSheets["map1bg"], 0);
	fg = new Sprite(&spriteSheets["map1fg"], 0);

	bg->setPos(-416.f, -300.f);
	fg->setPos(-416.f, -300.f);
}

Room::~Room()
{
	// Delete objects
	delete plyr;
	delete bg;
	delete fg;

	// Delete sprite sheets
	for (std::map<std::string, C2D_SpriteSheet>::iterator it = spriteSheets.begin(); it != spriteSheets.end(); ++it)
		C2D_SpriteSheetFree(it->second);
}

/* Accessors */
Player* Room::getPlayer()
{
	return plyr;
}

/* Other Functions */
void Room::handleInput(u32 kDown, u32 kHeld, u32 kUp)
{
	// Change skin
	if (kDown & KEY_R)
		plyr->setSkin(plyr->getSkin() + 1);

	if (kDown & KEY_L)
		plyr->setSkin(plyr->getSkin() - 1);

	// Move left/right
	if (kHeld & KEY_DRIGHT || kHeld & KEY_CPAD_RIGHT)
		plyr->moveRight();

	if (kHeld & KEY_DLEFT || kHeld & KEY_CPAD_LEFT)
		plyr->moveLeft();
}

void Room::draw()
{
	C2D_DrawSprite(bg->getSpr());
	plyr->draw();
	C2D_DrawSprite(fg->getSpr());
}