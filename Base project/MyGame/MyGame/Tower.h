#pragma once

#include "Engine/GameEngine.h"
#include "OffenseBot.h"
#include "Projectile.h"

enum TowerTypes { CheesyPoofs, SonicSquirrels };

class Tower : public GameObject {
public:
	Tower(TowerTypes itype, sf::Vector2f ipos);

	static int getCost(TowerTypes type);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
private:
	float range;
	float attackDelay;
	float attackTimer = 0.0;
	std::vector<GameObject> objectToTarget;
	float rotationSpeed;
	int level = 1;

	TowerTypes projectileType;
	int projectilesPerAttack;
	int projectilesShot = 1;
	float betweenProjectilesDelay;

	void attackAction(sf::Vector2f distanceToEnemy);
	void targetEnemy(float msElapsed);
	//virtual void levelUp();
};

typedef std::shared_ptr<Tower> TowerPtr;