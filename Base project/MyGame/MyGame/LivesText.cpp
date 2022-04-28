#include "LivesText.h"
#include "GameScene.h"
#include <sstream>

LivesText::LivesText(sf::Vector2f pos, int charSize, sf::Color textColor) {
	setupText(pos, charSize, textColor);
	assignTag("livesText");
}

void LivesText::update(sf::Time& elapsed) {
	GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();

	std::stringstream stream;
	stream << "Lives: " << currentScene_.getLives();

	text_.setString(stream.str());
	return;
}