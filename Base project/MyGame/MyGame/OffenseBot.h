#pragma once

#include "Engine/GameEngine.h"
const std::string OFFENSE_TAG = "offense";

enum operation { GoUp, GoRight, GoDown, GoLeft, Stop, Score };

class OffenseBot : public GameObject {
public:
	OffenseBot(sf::Vector2f ipos, float imovementSpeed);

	void update(sf::Time& elapsed);
	void draw();
private:
	float movementSpeed;
	std::vector<operation> directions{ GoDown, GoRight, GoUp, GoRight, GoDown, GoLeft, GoDown, GoRight, GoUp, GoRight, GoDown, GoRight, Score};
	int currentOperation = 0;
};

typedef std::shared_ptr<OffenseBot> OffenseBotPtr;