#include "Player.h"
#include "Game.h"

#define SPEED 300
#define MARGIN 20

#define SCORE_MARGIN_RIGHT 50
#define SCORE_MARGIN_TOP 50

Player::Player()
{
	texture.loadFromFile("res/player.png");
	setTexture(texture);

	moveToCenter();

	whiteHeartTexture.loadFromFile("res/heart_white.png");
	redHeartTexture.loadFromFile("res/heart_red.png");

	int x = WINDOW_WIDTH - SCORE_MARGIN_RIGHT;
	int y = SCORE_MARGIN_TOP;
	int w = redHeartTexture.getSize().x;
	for (int i = 0; i < PLAYER_FULL_LIFE; i++) {
		x -= w;
		hearts[i].setPosition(x, y);
	}
	life = PLAYER_FULL_LIFE;
	updateHearts();
}

void Player::handleEvent(Event& e)
{
	if (e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Left) {
			if (vector.x >= 0) vector.x -= SPEED;
		}
		else if (e.key.code == Keyboard::Right) {
			if (vector.x <= 0) vector.x += SPEED;
		}
		else if (e.key.code == Keyboard::Up) {
			if (vector.y >= 0) vector.y -= SPEED;
		}
		else if (e.key.code == Keyboard::Down) {
			if (vector.y <= 0) vector.y += SPEED;
		}
	}
	else if (e.type == Event::KeyReleased) {
		if (e.key.code == Keyboard::Left) {
			if (vector.x <= 0) vector.x += SPEED;
		}
		else if (e.key.code == Keyboard::Right) {
			if (vector.x >= 0) vector.x -= SPEED;
		}
		else if (e.key.code == Keyboard::Up) {
			if (vector.y <= 0) vector.y += SPEED;
		}
		else if (e.key.code == Keyboard::Down) {
			if (vector.y >= 0) vector.y -= SPEED;
		}
	}
}

void Player::moveToCenter(void)
{
	//const Texture& texture = *getTexture();
	//Vector2u size = texture.getSize();
	Vector2u size = getTexture()->getSize();
	Vector2f pos(
		WINDOW_WIDTH / 2 - (float)(size.x / 2),
		WINDOW_HEIGHT / 2 - (float)(size.y / 2)
	);
	setPosition(pos);
}

void Player::update()
{
	MovingSprite::update();
	const Vector2f& pos = getPosition();

	const float min_x = MARGIN, max_x = WINDOW_WIDTH - MARGIN - (float)size.x;
	const float min_y = MARGIN, max_y = WINDOW_HEIGHT - MARGIN - (float)size.y;

	if (pos.x < min_x) {
		setPosition(min_x, pos.y);
	}
	else if (pos.x > max_x) {
		setPosition(max_x, pos.y);
	}

	if (pos.y < min_y) {
		setPosition(pos.x, min_y);
	}
	else if (pos.y > max_y) {
		setPosition(pos.x, max_y);
	}
}

void Player::draw(RenderWindow& win)
{
	win.draw(*this);
	for (auto &heart : hearts) {
		win.draw(heart);
	}
}

bool Player::decreaseLife()
{
	life--;
	updateHearts();
	return life > 0;
}

bool Player::increaseLife()
{
	if (life >= PLAYER_FULL_LIFE) {
		return false;
	}
	life++;
	updateHearts();
	return true;
}

void Player::reset()
{
	life = PLAYER_FULL_LIFE;
	updateHearts();
	moveToCenter();
}

void Player::updateHearts()
{
	for (int i = 0; i < PLAYER_FULL_LIFE; i++) {
		//if (i < life) {
		//	hearts[i].setTexture(redHeartTexture);
		//}
		//else {
		//	hearts[i].setTexture(whiteHeartTexture);
		//}
		hearts[i].setTexture(i < life ? redHeartTexture : whiteHeartTexture);
	}
}
