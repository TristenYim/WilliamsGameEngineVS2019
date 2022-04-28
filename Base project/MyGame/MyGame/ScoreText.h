#pragma once

#include "Engine/GameEngine.h"

class ScoreText : public TextObject {
public:
	//Creates the score instance at position and sets the size and font color
	ScoreText(sf::Vector2f pos, int charSize, sf::Color textColor);

	//Methods overriden from GameObject
	void update(sf::Time& elapsed);
};

typedef std::shared_ptr<ScoreText> ScoreTextPtr;