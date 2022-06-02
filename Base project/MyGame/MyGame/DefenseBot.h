#pragma once

#include "Engine/GameEngine.h"

const float DRIVING_SPEED = 0.15;
const std::string DEFENSE_TAG = "defense";
enum direction { Stopped, Up, Right, Down, Left };

class DefenseBot : public GameObject {
public:
	DefenseBot(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
private:
	void moveInADirection(sf::Vector2f& neoPosition, direction direction_, int msElapsed);
};

typedef std::shared_ptr<DefenseBot> DefenseBotPtr;                