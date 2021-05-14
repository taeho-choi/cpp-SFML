#include "Game.h"

float Game::frameTime;

Game::Game() {
	txBg.loadFromFile("res/outerspace.png");
	spBg.setTexture(txBg);

	txPlayer.loadFromFile("res/player.png");
	spPlayer.setTexture(txPlayer);

	txBall.loadFromFile("res/missile.png");
}

void Game::Update() {
	Time diff = clock.restart();
	frameTime = diff.asSeconds();

	// Player Move
	spPlayer.Update();

	// Ball Move
	for (auto& ball : balls)
	{
		ball.Update();
	}
}

void Game::draw(RenderWindow &win)
{
	win.draw(spBg);
	for (auto& ball : balls) {
		win.draw(ball);
	}
	win.draw(spPlayer);
}

void Game::generateBall()
{
	MovingSprite ball;
	ball.setTexture(txBall);
	Vector2f vector;
	vector.x = (float)(rnd_engine() % 100 + 50);
	vector.y = (float)(rnd_engine() % 100 + 20);
	ball.setVector(vector);
	balls.push_back(ball);
}