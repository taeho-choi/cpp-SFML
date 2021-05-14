#include "MovingSprite.h"
#include "Game.h"

void MovingSprite::setVector(const Vector2f &vector)
{
	this->vector = vector;
}

const Vector2f MovingSprite::getVetor()
{
	return this->vector;
}

extern float framTime;

void MovingSprite::Update()
{
	float dx = vector.x * Game::frameTime;
	float dy = vector.y * Game::frameTime;
	move(dx, dy);
}
