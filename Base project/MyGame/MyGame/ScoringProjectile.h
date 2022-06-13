#pragma once

#include "Engine/GameEngine.h"

class ScoringProjectile : public GameObject {
public:
	ScoringProjectile(sf::Vector2f ipos, bool willItHit);

	void update(sf::Time& elapsed);
	void draw();
	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherGameObject);
private:
	sf::Vector2f movementVector;
};

typedef std::shared_ptr<ScoringProjectile> ScoringProjectilePtr;