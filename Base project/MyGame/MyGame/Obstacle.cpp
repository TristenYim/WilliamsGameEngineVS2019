#include "Obstacle.h"

std::vector<std::string> Obstacle::obstacleTextureVariants;

Obstacle::Obstacle(sf::Vector2f ipos) {
	sprite_.setPosition(ipos);
	sprite_.setTexture(GAME.getTexture(obstacleTextureVariants[1 + rand() % obstacleTextureVariants.size() -1]));
	assignTag("obstacle");
}

void Obstacle::initializeObstacleTextureVariants(std::vector<std::string> itextureVariants) {
	for (int index = 0; index < itextureVariants.size(); index++) {
		obstacleTextureVariants.push_back(itextureVariants[index]);
	}
	return;
}

void Obstacle::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect Obstacle::getCollisionRect() {
	return sprite_.getGlobalBounds();
}