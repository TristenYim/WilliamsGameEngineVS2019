#pragma once

#include "Engine/GameEngine.h"

class Obstacle : public GameObject {
public:
	Obstacle(sf::Vector2f ipos, sf::Texture& texture_);

	void draw();
	sf::FloatRect getCollisionRect();
private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<Obstacle> ObstaclePtr;