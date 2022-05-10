#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f ipos, sf::Texture texture_) {
	sprite_.setTexture(texture_);
	sprite_.setPosition(ipos);
	assignTag("obstacle");
}

void Obstacle::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}