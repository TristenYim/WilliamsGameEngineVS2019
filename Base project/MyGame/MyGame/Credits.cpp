#include "Credits.h"
#include <sstream>

int Credits::credit;

Credits::Credits(sf::Vector2f pos, int charSize, sf::Color textColor, int icredit) {
	setupText(pos, charSize, textColor);
	credit = icredit;
	assignTag("creditsobject");
}

void Credits::addCredit(int creditToAdd) {
	credit += creditToAdd;
	return;
}

int Credits::getCredit() {
	return credit;
}


void Credits::update(sf::Time& elapsed) {
	std::stringstream stream;
	stream << "Credits: " << credit;

	text_.setString(stream.str());
	return;
}