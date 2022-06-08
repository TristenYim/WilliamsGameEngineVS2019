#pragma once

#include "Engine/GameEngine.h"
#include "OffenseBot.h"

class Tower : public GameObject {
public:
	Tower(sf::Vector2f ipos, float irange, float iattackDelay, float iprojectileSpeed);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
protected:
	float range;
	float attackDelay;
	float attackTimer = 0.0;
	std::vector<GameObject> objectToTarget;
	float rotationSpeed = 0.5;
	float projectileSpeed;
	float projectileDamage;
	int level = 1;

	void attackAction(sf::Vector2f distanceToEnemy);
	//virtual void levelUp();
};

typedef std::shared_ptr<Tower> TowerPtr;