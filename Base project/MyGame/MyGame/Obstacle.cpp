#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f ipos, sf::Texture& texture_) {
	sprite_.setPosition(ipos);
	sprite_.setTexture(texture_);
	assignTag("obstacle");
}

void Obstacle::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect Obstacle::getCollisionRect() {
	return sprite_.getGlobalBounds();
}