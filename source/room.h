#ifndef ROOM_H
#define ROOM_H

#include <citro2d.h>
#include <string>
#include <map>

#include "player.h"
#include "sprite.h"

class Room
{
	private:
		std::map<std::string, C2D_SpriteSheet> spriteSheets;
		Player* plyr = nullptr;
		Sprite* bg = nullptr;
		Sprite* fg = nullptr;
	public:
		Room();
		~Room();

		Player* getPlayer();

		void handleInput(u32 kDown, u32 kHeld, u32 kup);
		void draw();
};

#endif
