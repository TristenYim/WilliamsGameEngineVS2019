#pragma once

#include "Engine/GameEngine.h"

class EndingText : public TextObject {
public:
	EndingText(std::string message, sf::Color textColor);

	void update(sf::Time& elapsed);
};

typedef std::shared_ptr<EndingText> EndingTextPtr;