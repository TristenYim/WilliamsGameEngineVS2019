#pragma once

#include "Engine/GameEngine.h"
const std::string OFFENSE_TAG = "offense";

enum Operation { GoUp, GoRight, GoDown, GoLeft, Stop, Score };

class OffenseBot : public GameObject {
public:
	OffenseBot(sf::Vector2f ipos, float imovementSpeed);

	void update(sf::Time& elapsed);
	void draw();
private:
	float movementSpeed;
	std::vector<Operation> directions{ GoDown, GoRight, GoUp, GoRight, GoDown, GoLeft, GoDown, GoRight, GoUp, GoRight, GoDown, GoRight, Score };
	int currentOperation = 0;
	void go(Operation& direction, sf::Vector2f& neoPosition, float msElapsed);
};

typedef std::shared_ptr<OffenseBot> OffenseBotPtr;