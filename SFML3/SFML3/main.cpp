#include <SFML/Graphics.hpp>
#include <random>
#include "Game.h"

using namespace sf;

int main()
{
	Game game;

	RenderWindow win(VideoMode(800, 600), "Game");

	while (win.isOpen()) {
		Event e;
		while (win.pollEvent(e)) {
			if (e.type == Event::Closed) {
				win.close();
				break;
			}
			if (e.type == Event::KeyPressed) {
				//if (e.key.code == keyboard::left) {
				//	if (playervector.x >= 0) playervector.x -= playerspeed;
				//}
				//else if (e.key.code == keyboard::right) {
				//	if (playervector.x <= 0) playervector.x += playerspeed;
				//}
				//if (e.key.code == keyboard::up) {
				//	if (playervector.y >= 0) playervector.y -= playerspeed;
				//}
				//else if (e.key.code == keyboard::down) {
				//	if (playervector.y <= 0) playervector.y += playerspeed;
				//}
				if (e.key.code == Keyboard::Escape) {
					win.close();
					break;
				}
				if (e.key.code == Keyboard::Space) {
					game.generateBall();
					//spBall.setPosition(0, 0);
				}
			}
			else if (e.type == Event::KeyReleased) {
				//if (e.key.code == Keyboard::Left) {
				//	if (playerVector.x <= 0) playerVector.x += playerSpeed;
				//}
				//else if (e.key.code == Keyboard::Right) {
				//	if (playerVector.x >= 0) playerVector.x -= playerSpeed;
				//}
				//if (e.key.code == Keyboard::Up) {
				//	if (playerVector.y <= 0) playerVector.y += playerSpeed;
				//}
				//else if (e.key.code == Keyboard::Down) {
				//	if (playerVector.y >= 0) playerVector.y -= playerSpeed;
				//}
			}

		}

		game.Update();
		game.draw(win);

		win.display();
	}
	return 0;
}