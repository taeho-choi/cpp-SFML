#pragma once
#include "MovingSprite.h"

#define PLAYER_FULL_LIFE 5

class Player : public MovingSprite
{
	int life;
	Texture texture;
	Sprite hearts[PLAYER_FULL_LIFE];
	Texture whiteHeartTexture;
	Texture redHeartTexture;
public:
	Player();
	void handleEvent(Event& e);
	void moveToCenter(void);
	virtual void update();
	void draw(RenderWindow& win);
	bool decreaseLife();
	bool increaseLife();

private:
	void updateHearts();
};