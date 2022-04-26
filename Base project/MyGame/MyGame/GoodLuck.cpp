/*#include "GoodLuck.h"
#include <sstream>

GoodLuck::GoodLuck() {
	goodLuckText_.setFont(GAME.getFont("Courneuf-Regular.ttf"));
	//TODO: Put the text in the center of the screen
	float windowLength = GAME.getRenderWindow().getSize().x;
	float windowWidth = GAME.getRenderWindow().getSize().y;
	//See above
	goodLuckText_.setCharacterSize(108);
	goodLuckText_.setColor(sf::Color::Yellow);
	assignTag("goodluck");
}

void GoodLuck::draw() {
	GAME.getRenderWindow().draw(goodLuckText_);
}

void GoodLuck::update(sf::Time& elapsed) {
	Scene& currentScene_ = (Scene&)GAME.getCurrentScene();

	std::stringstream stream;
	stream << "Good Luck!!!";

	goodLuckText_.setString(stream.str());
}*/