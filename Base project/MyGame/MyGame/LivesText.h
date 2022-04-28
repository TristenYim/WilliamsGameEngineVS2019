#pragma once

#include "Engine/GameEngine.h"

class LivesText : public TextObject {
public:
	//Makes the lives text instance at position and sets the character size and font color
	LivesText(sf::Vector2f pos, int charSize, sf::Color textColor);

	//Methods overriden from GameObject
	void update(sf::Time& elapsed);
};

typedef std::shared_ptr<LivesText> LivesTextPtr;