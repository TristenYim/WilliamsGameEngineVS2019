#pragma once

#include "Engine/GameEngine.h"

class Projectile : public GameObject {
public:
	Projectile(sf::Vector2f ipos, sf::Vector2f distanceFromEnemy, std::string itexture, float speed, int idamage);

	void setTarget(sf::Vector2f distanceFromEnemy);
	int getDamage();

	void update(sf::Time& elapsed);
	void draw();
	sf::FloatRect getCollisionRect();
private:
	sf::Vector2f directionalSpeed;
	float speed;
	int damage;
};

typedef std::shared_ptr<Projectile> ProjectilePtr;