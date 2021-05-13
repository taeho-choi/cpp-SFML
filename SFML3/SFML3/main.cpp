#include <SFML/Graphics.hpp>

using namespace sf;


int main()
{
	RenderWindow win(VideoMode(800, 600), "Game");
	Sprite spBg;
	Texture txBg;
	txBg.loadFromFile("res/outerspace.png");
	spBg.setTexture(txBg);

	Sprite spPlayer;
	Texture txPlayer;
	txPlayer.loadFromFile("res/player.png");
	spPlayer.setTexture(txPlayer);

	while (win.isOpen()) {
		Event e;
		while (win.pollEvent(e)) {
			if (e.type == Event::Closed) {
				win.close();
				break;
			}
			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Left) {
					spPlayer.move(-10, 0);
				}
				else if (e.key.code == Keyboard::Right) {
					spPlayer.move(10, 0);
				}
				if (e.key.code == Keyboard::Up) {
					spPlayer.move(0, -10);
				}
				else if (e.key.code == Keyboard::Down) {
					spPlayer.move(0, 10);
				}
			}
		}
		win.draw(spBg);
		win.draw(spPlayer);
		win.display();
	}
	return 0;
}