#include "player.h"

#include <math.h>

Player::Player(C2D_SpriteSheet* sS, unsigned int s)
{
	spriteSheet = sS;
	skin = s;

	setSkin(s);
}

Player::~Player()
{
	for (unsigned int i = 0; i < 4; i++)
		delete sprites[i];
}

/* Accessors */
unsigned int Player::getSkin()
{
	return skin;
}

/* Setters */
void Player::setPos(float xx, float yy)
{
	x = xx;
	y = yy;

	for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		(*it)->setPos(x, y);
}

void Player::setScale(float xs, float ys)
{
	xScale = xs;
	yScale = ys;
	
	for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		(*it)->setScale(xScale, yScale);
}

void Player::setSkin(unsigned int s)
{
	if (s >= 16) return;
	skin = s;
	
	for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		delete (*it);
	sprites.clear();

	unsigned int offset = skin * 4;

	for (unsigned int i = 0; i < 4; i++)
	{
		Sprite* spr = new Sprite(spriteSheet, offset + i);
		spr->setPos(x, y);
		spr->setCenter(.5f, .5f);
		spr->setScale(xScale, yScale);

		sprites.push_back(spr);
	}
}

void Player::moveRight()
{
	setPos(x + 2, y);
	setScale(1.f, 1.f);
}

void Player::moveLeft()
{
	setPos(x - 2, y);
	setScale(-1.f, 1.f);
}

void Player::draw()
{
	frameTimer += 4.f / 60.f;
	frameTimer = fmodf(frameTimer, 4.f);

	unsigned int frame = anim[floor(frameTimer)];
	Sprite* spr = sprites[frame];
	C2D_DrawSprite(spr->getSpr());
}
