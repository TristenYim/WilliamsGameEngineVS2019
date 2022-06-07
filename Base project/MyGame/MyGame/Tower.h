#pragma once

#include "Engine/GameEngine.h"
#include "OffenseBot.h"

class Tower : public GameObject {
public:
	Tower(sf::Vector2f ipos, float irange, float iattackDelay);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
protected:
	float attackDelay;
	float attackTimer = 0;
	float projectileDamage;
	float projectileSpeed;
	float range;
	int level = 1;

	void attackAction(GameObject botToAttack);
	//virtual void levelUp();
};

typedef std::shared_ptr<Tower> TowerPtr;