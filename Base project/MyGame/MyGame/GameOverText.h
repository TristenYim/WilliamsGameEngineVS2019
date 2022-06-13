#pragma once

#include "Engine/GameEngine.h"

class GameOverText : public TextObject {
public:
	GameOverText();

	void update(sf::Time& elapsed);
};

typedef std::shared_ptr<GameOverText> GameOverTextPtr;