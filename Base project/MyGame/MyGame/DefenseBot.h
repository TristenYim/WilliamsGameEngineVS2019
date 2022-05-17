#pragma once

#include "Engine/GameEngine.h"

const float DRIVING_SPEED = 0.15f;

class DefenseBot : public GameObject {
public:
	DefenseBot(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherObject_);
private:
	bool justPressedW;
	bool justPressedA;
	bool justPressedS;
	bool justPressedD;
};

typedef std::shared_ptr<DefenseBot> DefenseBotPtr;                