#include "player.h"

#include <math.h>

Player::Player(C2D_SpriteSheet spriteSheet, unsigned int skin)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		unsigned int offset = skin * 4;

		Sprite* spr = new Sprite(spriteSheet, offset + i);
		spr->setPos(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		spr->setCenter(.5f, .5f);

		sprites.push_back(spr);
	}
}

Player::~Player()
{
	for (unsigned int i = 0; i < 4; i++)
		delete sprites[i];
}

void Player::draw()
{
	frameTimer += 4.f / 60.f;
	frameTimer = fmodf(frameTimer, 4.f);

	unsigned int frame = anim[floor(frameTimer)];
	Sprite* spr = sprites[frame];
	C2D_DrawSprite(spr->getSpr());
}