#include "ScoreText.h"
#include "GameScene.h"
#include <sstream>

ScoreText::ScoreText(sf::Vector2f pos, int charSize, sf::Color textColor) {
	setupText(pos, charSize, textColor);
	assignTag("scoreText");
}

void ScoreText::update(sf::Time& elapsed) {
	GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();

	std::stringstream stream_;
	stream_ << "Score: " << currentScene_.getScore();

	text_.setString(stream_.str());
	return;
}