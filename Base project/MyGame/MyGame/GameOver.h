#pragma once

#include "Engine/GameEngine.h"

class GameOver : public TextObject {
public:
	//Creates the text
	GameOver(int score);

	//Methods overriden from GameObject
	void update(sf::Time& elapsed);
};

typedef std::shared_ptr<GameOver> GameOverPtr;