#include "Background.h"

const float SCROLL_SPEED = 4.0f;

Background::Background() {
	sprite_1.setTexture(GAME.getTexture("Resources/background.png"));
	sprite_2.setTexture(GAME.getTexture("Resources/background.png"));
	sprite_1.setPosition(sf::Vector2f(500, 0));
	sprite_2.setPosition(sf::Vector2f(0, 1080));
	assignTag("background");
}

void Background::draw() {
	GAME.getRenderWindow().draw(sprite_1);
	GAME.getRenderWindow().draw(sprite_2);
	return;
}

void Background::update(sf::Time& elapsed) {
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f sprite_1pos = sprite_1.getPosition();
	sf::Vector2f sprite_2pos = sprite_2.getPosition();
	sprite_1pos.y += SCROLL_SPEED * msElapsed;
	sprite_2pos.y += SCROLL_SPEED * msElapsed;
	if (GAME.getRenderWindow().getSize().y < sprite_1pos.y) {
		sprite_1pos.y -= GAME.getRenderWindow().getSize().y;
	} else if (GAME.getRenderWindow().getSize().y < sprite_2pos.y) {
		sprite_2pos.y -= GAME.getRenderWindow().getSize().y;
	}
	sprite_1.setPosition(sprite_1pos);
	sprite_2.setPosition(sprite_2pos);
	return;
}