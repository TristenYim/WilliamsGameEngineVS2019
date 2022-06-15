#pragma once

#include "Engine/GameEngine.h"
#include "Projectile.h"

enum ExplosionStatus { Hitting, Exploding, Exploded };

class BombProjectile : public Projectile {
public:
	BombProjectile(sf::Vector2f ipos, std::string itexture, sf::Vector2f distanceFromEnemy, float speed, int idamage, bool ipierces, int ilevel);

	static void setupProjectileType();

	void update(sf::Time& elapsed);
	void handleCollision(GameObject& otherGameObject);
	sf::FloatRect getCollisionRect();
private:
	static std::vector<int> explosionDamages;
	static int explosionRange;
	int level;
	ExplosionStatus exploding_ = Hitting;
};

typedef std::shared_ptr<BombProjectile> BombProjectilePtr;