#ifndef ROOM_H
#define ROOM_H

#include <citro2d.h>
#include <string>
#include <vector>
#include <map>

#include "globals.h"
#include "player.h"
#include "block.h"

class Room
{
	private:
		std::map<std::string, C2D_SpriteSheet> spriteSheets;
		std::vector<Block*> blocks;
		Player* plyr = nullptr;
		Sprite* bg = nullptr;
		Sprite* fg = nullptr;
		float viewX = 0.f, viewY = 0.f;
	public:
		Room();
		~Room();

		Player* getPlayer();

		void handleInput(u32 kDown, u32 kHeld, u32 kUp);
		void draw();
};

#endif
