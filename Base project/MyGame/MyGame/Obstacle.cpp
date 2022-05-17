#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f ipos) {
	obstacleTextureVariants.push_back("Resources/Red Square.png");
	obstacleTextureVariants.push_back("Resources/Yellow Square.png");
	obstacleTextureVariants.push_back("Resources/Green Square.png");
	sprite_.setPosition(ipos);
	sprite_.setTexture(GAME.getTexture(obstacleTextureVariants[1 + rand() % obstacleTextureVariants.size() -1]));
	assignTag("obstacle");
}

void Obstacle::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect Obstacle::getCollisionRect() {
	return sprite_.getGlobalBounds();
}