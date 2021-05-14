#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "MovingSprite.h"
using namespace sf;

class Game
{
private:
	Sprite spBg;
	Texture txBg;

	MovingSprite spPlayer;
	Texture txPlayer;

	//Sprite spBall;
	std::vector<MovingSprite> balls;
	Texture txBall;
	//spBall.setTexture(txBall);

	//const int playerSpeed = 300;

	Clock clock;
	std::mt19937 rnd_engine;


public:
	Game();
	void Update();
	static float frameTime;
	void draw(RenderWindow &win);
	void generateBall();
};

