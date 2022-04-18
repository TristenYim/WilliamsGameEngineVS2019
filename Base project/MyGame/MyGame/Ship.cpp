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