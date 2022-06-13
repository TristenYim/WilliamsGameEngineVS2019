#pragma once

#include "Engine/GameEngine.h"
const std::string OFFENSE_TAG = "offense";

enum Operation { GoUp, GoRight, GoDown, GoLeft, Stop, GoScore };

class OffenseBot : public GameObject {
public:
	OffenseBot(sf::Vector2f ipos, float imovementSpeed, bool spawnOnBottom, int ipercentChanceOfScoring, float iscoringDelay);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
	sf::Vector2f getPosition();
private:
	float movementSpeed;
	std::vector<Operation> directions;
	int currentOperation = 0;
	float scoringTimer = scoringDelay;
	float scoringDelay;
	int percentChanceOfScoring;

	void move(float msElapsed);
	void scoreAction();

	OffenseBot(OffenseBot const&);
};

typedef std::shared_ptr<OffenseBot> OffenseBotPtr;