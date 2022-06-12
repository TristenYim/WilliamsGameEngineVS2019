#pragma once

#include "Engine/GameEngine.h"

class Obstacle : public GameObject {
public:
	Obstacle(sf::Vector2f ipos);

	static void initializeObstacleTextureVariants(std::vector<std::string> itextureVariants);

	void draw();
	sf::FloatRect getCollisionRect();
private:
	static std::vector<std::string> obstacleTextureVariants;
};

typedef std::shared_ptr<Obstacle> ObstaclePtr;