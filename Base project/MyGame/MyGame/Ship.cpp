#include "Ship.h"

Ship::Ship() {
	sprite_.setTexture(GAME.getTexture("Resources/Ship.png"));
	sprite_.setPosition(sf::Vector2f(192, 540));
}

Ship::Ship(int x, int y) {
	sprite_.setTexture(GAME.getTexture("Resources/Ship.png"));
	sprite_.setPosition(sf::Vector2f(x, y));
}

void Ship::draw() {
	GAME.getRenderWindow().draw(sprite_);
}

void Ship::update(sf::Time& elapsed) {
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;
	int msElapsed = elapsed.asMilliseconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y -= SPEED * msElapsed;
}