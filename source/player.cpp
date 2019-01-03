#include "player.h"

#include <math.h>
#include <algorithm>
#include "room.h"

Player::Player(C2D_SpriteSheet* sS, unsigned int s, Room* r)
{
	spriteSheet = sS;
	skin = s;
	level = r;

	setSkin(s);
}

Player::~Player()
{
	for (unsigned int i = 0; i < 4; i++)
		delete sprites[i];
}

/* Accessors */
float Player::getX()
{
	return x;
}

float Player::getY()
{
	return y;
}

unsigned int Player::getSkin()
{
	return skin;
}

/* Setters */
void Player::setPos(float xx, float yy, float offsetX = 0, float offsetY = 0)
{
	x = xx;
	y = yy;

	for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		(*it)->setPos(ceil(x - offsetX), ceil(y - offsetY));
}

void Player::setOffset(float offsetX, float offsetY)
{
	setPos(x, y, offsetX, offsetY);
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
		spr->setPos(ceil(x), ceil(y));
		spr->setCenter(16.f, 16.f);
		spr->setScale(xScale, yScale);

		sprites.push_back(spr);
	}
}

std::vector<Block*> Player::allCollisions(float xx, float yy) const
{
	std::vector<Block*> result;
	Rect* myRect = new Rect(x - 4, y - 10, 8, 24);
	Rect* tempRect = new Rect(xx + myRect->getX() - x,
							  yy + myRect->getY() - y,
							  myRect->getW(),
							  myRect->getH());

	auto const &blocks = level->getBlocks();
	std::copy_if(blocks.begin(), blocks.end(), std::back_inserter(result), [&](Block* const &elem)
	{
		return tempRect->intersects(elem->getRect());
	});

	delete myRect;
	delete tempRect;

	return result;
}

bool Player::placeFree(float xx, float yy) const
{
	Rect* tempRect = new Rect(xx - 4, yy - 10, 8, 24);

	auto const &blocks = level->getBlocks();
	return std::none_of(blocks.begin(), blocks.end(), [&](Block* const &elem)
	{
		return tempRect->intersects(elem->getRect());
	});
}

/* Other Functions */
void Player::moveRight()
{
	if (!placeFree(x + 2, y)) return;
	setPos(x + 2, y);
	setScale(1.f, 1.f);
}

void Player::moveLeft()
{
	if (!placeFree(x - 2, y)) return;
	setPos(x - 2, y);
	setScale(-1.f, 1.f);
}

void Player::jump()
{
	if (dy == 0) dy = -9.f;
}

void Player::loopAroundMap()
{
	float xPrev = x;
	float yPrev = y;

	if (x < -1) x += ROOM_WIDTH;
	else if (x > ROOM_WIDTH + 1) x -= ROOM_WIDTH;

	if (y < -1) y += ROOM_HEIGHT;
	else if (y > ROOM_HEIGHT + 1) y -= ROOM_HEIGHT;

	if (x != xPrev || y != yPrev) setPos(x, y);
}

void Player::pushOutOfSolids()
{
	for (auto b : allCollisions(x, y))
	{
		auto bBox = b->getRect();
		setPos(x, floor(std::min<float>(y, bBox->getY() - 10)));
	}
}

void Player::applyGravityOnce()
{
	if (placeFree(x, y + 1)) dy += gravity;
	else if (dy > 0.f) dy = 0.f;

	if (dy > maxFallSpeed) dy = maxFallSpeed;
}

void Player::applyVelocityOnce()
{
	for (float i = fabs(dy); i > 0; i--)
	{
		float j = copysign(i, dy);
		if (placeFree(x, y + j))
		{
			y += j;
			break;
		}
	}

	bool shouldSlopeWalk = false;//dy == 0 && !placeFree(x, y + 1);
	for (float i = fabs(dx); i > 0; i--)
	{
		float xAdjust = copysign(i, dx);

		// We search for a y-adjustment, these are our bounds
		float yAdjustStart = 0;
		float yAdjustEnd = 0;

		if (shouldSlopeWalk)
		{
			yAdjustStart = round(maxFallSpeed);
			yAdjustEnd = -4;
		}

		// Find an appropriate y-adjustment for slope walking
		for (double yAdjust = yAdjustStart; yAdjust >= yAdjustEnd; yAdjust--)
		{
			if (placeFree(x + xAdjust, y + yAdjust))
			{
				x += xAdjust;
				y += yAdjust;

				return;
			}
		}
	}
}

void Player::draw()
{
	applyGravityOnce();
	applyVelocityOnce();
	loopAroundMap();
	pushOutOfSolids();

	if (dy < 0.f && !placeFree(x, y - 1)) dy = 0.f;

	if (x != xLast)
	{
		frameTimer += 6.f / 60.f;
		frameTimer = fmodf(frameTimer, 4.f);
	}
	else frameTimer = .8f;

	unsigned int frame = anim[floor(frameTimer)];
	Sprite* spr = sprites[frame];
	C2D_DrawSprite(spr->getSpr());

	xLast = x;
	yLast = y;
}
