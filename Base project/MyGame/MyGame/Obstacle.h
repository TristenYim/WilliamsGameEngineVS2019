#pragma once

#include "Engine/GameEngine.h"

class Obstacle : public GameObject {
public:
	// Creates the obstacle
	Obstacle(sf::Vector2f ipos, sf::Texture texture_);

	// Methods overriden from GameObject
	void draw();
private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<Obstacle> ObstaclePtr;