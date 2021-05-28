#include "Game.h"

#define MAX_BALL_COUNT 10
#define MAX_ITEM_COUNT 3

float Game::frameTime;

Game::Game(RenderWindow& win) : win{ win }
{
	inPlay = true;

	txBg.loadFromFile("res/outerspace.png");
	spBg.setTexture(txBg);

	txBall.loadFromFile("res/missile.png");
	
	txItem.loadFromFile("res/item.png");

	txGameOver.loadFromFile("res/gameover.png");
	spGameOver.setTexture(txGameOver);
	Vector2u size = txGameOver.getSize();
	spGameOver.setPosition(
		(WINDOW_WIDTH - size.x) / 2.0f,
		(WINDOW_HEIGHT - size.y) / 2.0f
	);
}

void Game::update(void)
{
	if (!inPlay) {
		return;
	}
	Time diff = clock.restart();
	frameTime = diff.asSeconds();

	spPlayer.update();

	for (auto& ball : balls) {
		ball.update();
	}
	for (auto& item : items) {
		item.update();
	}

	for (auto it = balls.begin(); it != balls.end(); it++) {
		Ball& ball = *it;
		if (ball.isOutOfScreen()) {
			balls.erase(it);
			printf("[-]Ball count = %d\n", balls.size());
			break;
		}
		if (spPlayer.collides(ball)) {
			balls.erase(it);
			bool alive = spPlayer.decreaseLife();
			if (!alive) {
				printf("Dead. Gameover screen should follow\n");
				inPlay = false;
			}
			printf("[Collision !!!] %d\n", balls.size());
			break;
		}
	}

	for (auto it = items.begin(); it != items.end(); it++) {
		Ball& item = *it;
		if (item.isOutOfScreen()) {
			items.erase(it);
			printf("[-]Ball count = %d\n", items.size());
			break;
		}
		if (spPlayer.collides(item)) {
			items.erase(it);
			bool increased = spPlayer.increaseLife();
			if (!increased) {
				printf("Life is already full\n");
			}
			break;
		}
	}

	if (balls.size() < MAX_BALL_COUNT) {
		generateBall();
	}
	if (items.size() < MAX_ITEM_COUNT) {
		generateItem();
	}
}

void Game::draw(void)
{
	win.draw(spBg);
	for (auto& ball : balls) {
		win.draw(ball);
	}
	for (auto& item : items) {
		win.draw(item);
	}

	spPlayer.draw(win);

	if (!inPlay) {
		win.draw(spGameOver);
	}
	//win.draw(spPlayer);
}

void Game::handleEvent(Event& e)
{
	//if (e.type == Event::KeyPressed) {
	//	if (e.key.code == Keyboard::Space) {
	//		generateBall();
	//	}
	//}

	spPlayer.handleEvent(e);
}

void Game::generateBall(void)
{
	Ball ball(txBall);
	balls.push_back(ball);
	printf("[+]Ball count = %d\n", balls.size());
}

void Game::generateItem(void)
{
	Ball item(txItem, false);
	items.push_back(item);
}

static std::mt19937 rnd_engine;

unsigned Game::getRandom(int bound)
{
	return rnd_engine() % bound;
}

float Game::getRandom(void)
{
	return rnd_engine() % 1000000 / 1000000.0f;
}