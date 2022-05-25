#pragma once

#include "Engine/GameEngine.h"

class OffenseBot : public GameObject {
public:
	OffenseBot(sf::Vector2f ipos);

	void draw();
};

typedef std::shared_ptr<OffenseBot> OffenseBotPtr;