#include "ScoreText.h"
#include "GameScene.h"
#include <sstream>

ScoreText::ScoreText(sf::Vector2f pos, int charSize, sf::Color textColor) {
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(pos);
	text_.setCharacterSize(charSize);
	text_.setColor(textColor);
	assignTag("scoreText");
}

void ScoreText::draw() {
	GAME.getRenderWindow().draw(text_);
}

void ScoreText::update(sf::Time& elapsed) {
	GameScene& currentScene = (GameScene&)GAME.getCurrentScene();

	std::stringstream stream;
	stream << "Score: " << currentScene.getScore();

	text_.setString(stream.str());
}