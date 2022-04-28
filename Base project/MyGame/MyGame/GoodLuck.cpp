#include "GoodLuck.h"
#include <sstream>

GoodLuck::GoodLuck() {
	//TODO: Put the text in the center of the screen
	float windowLength = GAME.getRenderWindow().getSize().x / 2.0;
	float windowHeight = GAME.getRenderWindow().getSize().y / 2.0;
	//See above
	setupText(sf::Vector2f(windowLength, windowHeight), 108, sf::Color::Yellow);
	assignTag("goodluck");
}

void GoodLuck::update(sf::Time& elapsed) {
	Scene& currentScene_ = (Scene&)GAME.getCurrentScene();

	std::stringstream stream_;
	stream_ << "Good Luck!!!";

	text_.setString(stream_.str());
	return;
}