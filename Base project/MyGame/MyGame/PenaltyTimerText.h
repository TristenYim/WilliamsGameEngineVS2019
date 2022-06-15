#pragma once

#include "Engine/GameEngine.h"

class PenaltyTimerText : public TextObject {
public:
	PenaltyTimerText(sf::Vector2f ipos, int icharSize, sf::Color itextColor);

	static void setSecondsInTimer(int neoSeconds);
	static void setVisibility(bool neoVisibility);
	static void setColor(sf::Color neoColor);

	void draw();
	void update(sf::Time& elapsed);
private:
	static sf::Text text_;
	static int secondsInTimer;
	static bool visibility;
};

typedef std::shared_ptr<PenaltyTimerText> PenaltyTimerTextPtr;