#pragma once

#include "Engine/GameEngine.h"

const float DRIVING_SPEED = 0.1f;

class DefenseBot : public GameObject {
public:
	DefenseBot(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
	void draw();
private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<DefenseBot> DefenseBotPtr;