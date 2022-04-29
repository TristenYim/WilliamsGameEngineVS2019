#include "GoodLuck.h"
#include <sstream>

GoodLuck::GoodLuck() {
	//TODO: Put the text in the center of the screen
	float windowLength = GAME.getRenderWindow().getSize().x;
	float windowHeight = GAME.getRenderWindow().getSize().y;
	//See above
	setupText(sf::Vector2f(windowLength / 2.0 - 162.0, windowHeight / 2.0 - 54), 108.0, sf::Color::Yellow);
	assignTag("goodluck");
}

void GoodLuck::changeColor(sf::Color neocolor) {
	text_.setColor(neocolor);
	return;
}

void GoodLuck::update(sf::Time& elapsed) {
	Scene& currentScene_ = (Scene&)GAME.getCurrentScene();

	std::stringstream stream_;
	stream_ << "Good Luck!!!";

	text_.setString(stream_.str());
	return;
}