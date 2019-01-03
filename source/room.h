#ifndef ROOM_H
#define ROOM_H

#include <citro2d.h>
#include <string>
#include <vector>
#include <map>

#include "player.h"
#include "block.h"

#define ROOM_WIDTH 832
#define ROOM_HEIGHT 600

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
