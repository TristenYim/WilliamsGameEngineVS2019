#pragma once

#include "Engine/GameEngine.h"

class Tower : public GameObject {
public:
	Tower(sf::Vector2f ipos);

	//void update(sf::Time& elapsed);
	void draw();
protected:
	float attackDelay;
	float attackTimer;
	float projectileDamage;
	float projectileSpeed;
	float range;
	int level = 1;
	bool objectInRange = false;

	//virtual void attackAction();
	//virtual void levelUp();
};

typedef std::shared_ptr<Tower> TowerPtr;