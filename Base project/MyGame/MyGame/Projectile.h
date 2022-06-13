#pragma once

#include "Engine/GameEngine.h"

class Projectile : public GameObject {
public:
	Projectile(sf::Vector2f ipos, sf::Vector2f distanceFromEnemy, float speed);

	void update(sf::Time& elapsed);
	void draw();
	sf::FloatRect getCollisionRect();
private:
	sf::Vector2f directionalSpeed;
	int damage;
};

typedef std::shared_ptr<Projectile> ProjectilePtr;