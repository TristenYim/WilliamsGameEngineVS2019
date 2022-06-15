#pragma once

#include "Engine/GameEngine.h"

const float DRIVING_SPEED = 0.15;
const std::string DEFENSE_TAG = "defense";
enum direction { Stopped, Up, Right, Down, Left };

class DefenseBot : public GameObject {
public:
	DefenseBot(sf::Vector2f ipos);

	static bool isAttacking();

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
private:
	float blockingTimer;
	int blockingDelay;
	int blockingCooldown;
	int blockingPenaltyCooldown;

	float attackCooldownTimer;
	float attackCooldown;
	static bool attacking;

	void moveInADirection(sf::Vector2f& neoPosition, direction direction_, int msElapsed);
	void penaltyActions(float msElapsed);
	void attackActions(float msElapsed);
};

typedef std::shared_ptr<DefenseBot> DefenseBotPtr;                