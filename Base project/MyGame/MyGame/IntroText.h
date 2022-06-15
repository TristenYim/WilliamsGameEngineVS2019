#pragma once

#include "Engine/GameEngine.h"

class IntroText : public TextObject {
public:
	IntroText(sf::Vector2f ipos, int icharSize, sf::Color itextColor);

	void update(sf::Time& elapsed);
};

typedef std::shared_ptr<IntroText> IntroTextPtr;