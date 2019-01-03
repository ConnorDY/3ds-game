#include "room.h"

#include <3ds.h>
#include "globals.h"

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

	bg->setPos(-viewX, -viewY);
	fg->setPos(-viewX, -viewY);

	// Load blocks.txt
	FILE* f = fopen("romfs:/blocks.txt", "r");
	if (!f) svcBreak(USERBREAK_PANIC);

	unsigned int id = 1;

	char line[32];
	std::string delimiter = ", ";

	while (fgets(line, 32, f))
	{
		std::string str(line);
		std::string token;
		std::vector<int> values;
		size_t pos = 0;

		// Parse line
		while ((pos = str.find(delimiter)) != std::string::npos)
		{
			token = str.substr(0, pos);
			values.push_back(atoi(str.c_str()));
			str.erase(0, pos + delimiter.length());
		}
		values.push_back(atoi(str.c_str()));

		Block* b = new Block(values[0], values[1], values[2], values[3], id);
		blocks.push_back(b);
		id++;
	}
	if (!feof(f)) svcBreak(USERBREAK_PANIC);

	fclose(f);
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

	if (kHeld & KEY_DDOWN || kHeld & KEY_CPAD_DOWN)
		plyr->moveDown();

	if (kHeld & KEY_DUP || kHeld & KEY_CPAD_UP)
		plyr->moveUp();
}

void Room::draw()
{
	// Update view
	viewX = plyr->getX() - (SCREEN_WIDTH / 2);
	viewY = plyr->getY() - (SCREEN_HEIGHT / 2);

	if (viewX > ROOM_WIDTH - SCREEN_WIDTH) viewX = ROOM_WIDTH - SCREEN_WIDTH;
	else if (viewX < 0) viewX = 0;

	if (viewY > ROOM_HEIGHT - SCREEN_HEIGHT) viewY = ROOM_HEIGHT - SCREEN_HEIGHT;
	else if (viewY < 0) viewY = 0;

	// Move objects relative to the view
	plyr->setOffset(viewX, viewY);
	bg->setPos(-viewX, -viewY);
	fg->setPos(-viewX, -viewY);

	// Draw
	C2D_DrawSprite(bg->getSpr());
	plyr->draw();
	C2D_DrawSprite(fg->getSpr());

	for (std::vector<Block*>::iterator it = blocks.begin(); it != blocks.end(); ++it)
		(*it)->draw(viewX, viewY);
}