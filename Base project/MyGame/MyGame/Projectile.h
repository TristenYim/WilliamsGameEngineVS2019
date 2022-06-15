#pragma once

#include "Engine/GameEngine.h"

class Projectile : public GameObject {
public:
	Projectile() {};
	Projectile(sf::Vector2f ipos, std::string itexture, sf::Vector2f distanceFromEnemy, float speed, int idamage, bool ipierces);

	int getDamage();
	bool doesItPierce();

	void update(sf::Time& elapsed);
	void draw();
	sf::FloatRect getCollisionRect();
protected:
	void setup(sf::Vector2f ipos, std::string itexture, sf::Vector2f distanceFromEnemy, float speed, int idamage, bool ipierces);
	void updateSpritePosition(float msElapsed);
	int damage;
private:
	sf::Vector2f directionalSpeed;
	bool pierces;
};

typedef std::shared_ptr<Projectile> ProjectilePtr;