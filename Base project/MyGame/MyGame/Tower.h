#pragma once

#include "Engine/GameEngine.h"
#include "OffenseBot.h"

enum TowerTypes { CheesyPoofs };

class Tower : public GameObject {
public:
	Tower(TowerTypes itype, sf::Vector2f ipos);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
protected:
	float range;
	float attackDelay;
	float attackTimer = 0.0;
	std::vector<GameObject> objectToTarget;
	float rotationSpeed;
	int level = 1;
	std::string projectileTexture;
	float projectileSpeed;
	float projectileDamage;

	void attackAction(sf::Vector2f distanceToEnemy);
	void targetEnemy(float msElapsed);
	//virtual void levelUp();
};

typedef std::shared_ptr<Tower> TowerPtr;