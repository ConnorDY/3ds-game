#include "player.h"

#include <math.h>

Player::Player(C2D_SpriteSheet spriteSheet, unsigned int skin)
{
	x = SCREEN_WIDTH / 2.f;
	y = SCREEN_HEIGHT / 2.f;
	for (unsigned int i = 0; i < 4; i++)
	{
		unsigned int offset = skin * 4;

		Sprite* spr = new Sprite(spriteSheet, offset + i);
		spr->setPos(x, y);
		spr->setCenter(.5f, .5f);

		sprites.push_back(spr);
	}
}

Player::~Player()
{
	for (unsigned int i = 0; i < 4; i++)
		delete sprites[i];
}

void Player::setPos(float xx, float yy)
{
	x = xx;
	y = yy;

	for (unsigned int i = 0; i < 4; i++)
		sprites[i]->setPos(x, y);
}

void Player::moveRight()
{
	setPos(x + 2, y);
}

void Player::moveLeft()
{
	setPos(x - 2, y);
}

void Player::draw()
{
	frameTimer += 4.f / 60.f;
	frameTimer = fmodf(frameTimer, 4.f);

	unsigned int frame = anim[floor(frameTimer)];
	Sprite* spr = sprites[frame];
	C2D_DrawSprite(spr->getSpr());
}
