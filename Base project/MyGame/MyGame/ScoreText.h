#pragma once

#include "Engine/GameEngine.h"

class ScoreText : public GameObject {
public:
	//Creates the score instance at position
	ScoreText(sf::Vector2f pos, int charSize, sf::Color textColor);

	//Methods overriden from GameObject
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text text_;
};

typedef std::shared_ptr<ScoreText> ScoreTextPtr;