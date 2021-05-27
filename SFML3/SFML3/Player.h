#pragma once
#include "MovingSprite.h"
class Player : public MovingSprite
{
	int life;
public:
	void handleEvent(Event& e);
	void moveToCenter(void);
	virtual void update();
};