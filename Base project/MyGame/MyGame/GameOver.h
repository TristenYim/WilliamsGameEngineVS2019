#pragma once

#include "Engine/GameEngine.h"

class GameOver : public GameObject {
public:
	//Creates the text
	GameOver(int score);

	//Methods overriden from GameObject
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text gameOverText_;
};

typedef std::shared_ptr<GameOver> GameOverTextPtr