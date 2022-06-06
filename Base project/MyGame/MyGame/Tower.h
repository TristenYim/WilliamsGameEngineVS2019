#pragma once

#include "Engine/GameEngine.h"

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

	void attackAction();
	//virtual void levelUp();

	std::vector<GameObject> objectsToAttack;
};

typedef std::shared_ptr<Tower> TowerPtr;