#pragma once

#include "Engine/GameEngine.h"
const std::string OFFENSE_TAG = "offense";

enum Operation { GoUp, GoRight, GoDown, GoLeft, Stop, Score };

class OffenseBot : public GameObject {
public:
	OffenseBot(sf::Vector2f ipos, float imovementSpeed, bool spawnOnBottom);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
private:
	float movementSpeed;
	float scoringAccuracy;
	float scoringSpeed;
	std::vector<Operation> directions;
	int currentOperation = 0;

	void go(Operation& direction, sf::Vector2f& neoPosition, float msElapsed);
};

typedef std::shared_ptr<OffenseBot> OffenseBotPtr;