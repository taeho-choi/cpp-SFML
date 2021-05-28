#include "Game.h"
#pragma warning(disable: 4996)
#define INITIAL_MAX_BALL_COUNT 10
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
	scoreFont.loadFromFile("font/BAUHS93.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setPosition(50.f, 50.f);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Yellow);
}

void Game::update(void)
{
	Time diff = clock.restart();
	frameTime = diff.asSeconds();

	if (!inPlay) {
		return;
	}

	scoreValue += frameTime;
	updateScore();

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

	int maxBallCount = INITIAL_MAX_BALL_COUNT + (int)(scoreValue / 10);
	if (balls.size() < maxBallCount) {
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

	win.draw(scoreText);
	//win.draw(spPlayer);
}

void Game::handleEvent(Event& e)
{
	if (e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Enter) {
			if (!inPlay) {
				startGame();
			}
		}
	}

	spPlayer.handleEvent(e);
}

void Game::generateBall(void)
{
	float rate = 1.0f + scoreValue / 60.f;
	Ball ball(txBall, rate, true);
	balls.push_back(ball);
	printf("[+]Ball count = %d\n", balls.size());
}

void Game::generateItem(void)
{
	float rate = 1.0f + scoreValue / 60.f;
	Ball item(txItem, rate, false);
	items.push_back(item);
}

void Game::startGame(void)
{
	scoreValue = 0.0f;
	balls.clear();
	items.clear();
	spPlayer.reset();
	inPlay = true;
}

void Game::updateScore(void)
{
	char buff[30];
	sprintf(buff, "Score : %.1f", scoreValue);
	scoreText.setString(buff);
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