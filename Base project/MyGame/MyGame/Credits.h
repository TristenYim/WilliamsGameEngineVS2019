#pragma once

#include "Engine/GameEngine.h"

class Credits : public TextObject {
public:
	Credits(sf::Vector2f pos, int charSize, sf::Color textColor, int icredit);

	static void addCredit(int creditToAdd);
	static int getCredit();

	void update(sf::Time& elapsed);
private:
	static int credit;
};

typedef std::shared_ptr<Credits> CreditsPtr;