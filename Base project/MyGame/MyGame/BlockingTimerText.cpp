#include "BlockingTimerText.h"
#include <sstream>

sf::Text BlockingTimerText::text_;
int BlockingTimerText::secondsInTimer;
bool BlockingTimerText::visibility;

BlockingTimerText::BlockingTimerText(sf::Vector2f ipos, int icharSize, sf::Color itextColor) {
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(ipos);
	text_.setCharacterSize(icharSize);
	text_.setFillColor(itextColor);
	visibility = false;
	assignTag("blocking");
}

void BlockingTimerText::setSecondsInTimer(int neoSeconds) {
	secondsInTimer = neoSeconds;
	return;
}

void BlockingTimerText::setVisibility(bool neoVisibility) {
	visibility = neoVisibility;
	return;
}

void BlockingTimerText::setColor(sf::Color neoColor) {
	text_.setFillColor(neoColor);
 }

void BlockingTimerText::draw() {
	if (visibility) {
		GAME.getRenderWindow().draw(text_);
	}
	return;
}

void BlockingTimerText::update(sf::Time& elapsed) {
	std::stringstream stream;
	stream << secondsInTimer;

	text_.setString(stream.str());
	return;
}