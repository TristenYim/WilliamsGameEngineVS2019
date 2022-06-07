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

	void attackAction();
	//virtual void levelUp();

	// This list is used to store all offense bots in range in order to determine which ones can be targeted
	// Bots are added to this list whenever they are in range and are removed if they are out of range when the tower tries to attack
	// This is system is more efficient than the alternative (or at least I thought it was), searching every object every time the tower tries to attack
	std::list<GameObjectPtr> botsInRange;
};

typedef std::shared_ptr<Tower> TowerPtr;