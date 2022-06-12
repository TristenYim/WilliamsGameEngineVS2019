#pragma once

#include "Engine/GameEngine.h"

class Projectile : public GameObject {
public:
	Projectile(sf::Vector2f ipos, sf::Vector2f distanceFromEnemy, float speed);

	void draw();
	sf::FloatRect getCollisionRect();
	void update(sf::Time& elapsed);
private:
	sf::Vector2f directionalSpeed;
};

typedef std::shared_ptr<Projectile> ProjectilePtr;