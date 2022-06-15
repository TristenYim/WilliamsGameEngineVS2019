#include "PenaltyTimerText.h"
#include <sstream>

sf::Text PenaltyTimerText::text_;
int PenaltyTimerText::secondsInTimer;
bool PenaltyTimerText::visibility;

PenaltyTimerText::PenaltyTimerText(sf::Vector2f ipos, int icharSize, sf::Color itextColor) {
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(ipos);
	text_.setCharacterSize(icharSize);
	text_.setFillColor(itextColor);
	visibility = false;
	assignTag("blocking");
}

void PenaltyTimerText::setSecondsInTimer(int neoSeconds) {
	secondsInTimer = neoSeconds;
	return;
}

void PenaltyTimerText::setVisibility(bool neoVisibility) {
	visibility = neoVisibility;
	return;
}

void PenaltyTimerText::setColor(sf::Color neoColor) {
	text_.setFillColor(neoColor);
 }

void PenaltyTimerText::draw() {
	if (visibility) {
		GAME.getRenderWindow().draw(text_);
	}
	return;
}

void PenaltyTimerText::update(sf::Time& elapsed) {
	std::stringstream stream;
	stream << secondsInTimer;

	text_.setString(stream.str());
	return;
}