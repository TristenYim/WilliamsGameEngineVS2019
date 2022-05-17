#pragma once

#include "Engine/GameEngine.h"

class Obstacle : public GameObject {
public:
	Obstacle(sf::Vector2f ipos);

	void draw();
	sf::FloatRect getCollisionRect();
private:
	sf::Sprite sprite_;
	std::vector<std::string> obstacleTextureVariants;
};

typedef std::shared_ptr<Obstacle> ObstaclePtr;