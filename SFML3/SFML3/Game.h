#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "MovingSprite.h"
#include "Ball.h"
#include "Player.h"

using namespace sf;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Dodge Game 2021"

class Game
{
public:
	Game(RenderWindow& win);
	void update(void);
	void draw(void);
	void handleEvent(Event& e);

	static float frameTime;
	static unsigned getRandom(int bound);
	static float getRandom(void);

private:
	void generateBall(void);
	void generateItem(void);
	void startGame(void);
	void updateScore(void);

	RenderWindow& win;

	Sprite spBg;
	Texture txBg;

	Player spPlayer;
	bool inPlay;

	std::vector<Ball> balls;
	Texture txBall;

	std::vector<Ball> items;
	Texture txItem;

	Sprite spGameOver;
	Texture txGameOver;

	Clock clock;
	Text scoreText;
	Font scoreFont;
	float scoreValue;
};
