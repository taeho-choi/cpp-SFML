#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class MovingSprite : public Sprite
{
private:
	Vector2f vector;
public:
	void setVector(const Vector2f &vector);
	const Vector2f getVetor();
	void Update();
};

