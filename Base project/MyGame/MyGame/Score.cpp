#include "Score.h"
#include <sstream>

int Scores::playerScore;
int Scores::enemyScore;
sf::Sprite Scores::sprite_;

Scores::Scores(sf::Vector2f pos, int charSize, sf::Color textColor, int iplayerScore, sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Goal.png"));
	sprite_.setOrigin(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0);
	sprite_.setPosition(ipos);
	setCollisionCheckEnabled(true);
	setupText(pos, charSize, textColor);
	playerScore = iplayerScore;
	enemyScore = 0;
	assignTag("scoreobject");
}

void Scores::addEnemyScore(int scoreToAdd) {
	enemyScore += scoreToAdd;
	return;
}

void Scores::removePlayerScore(int scoreToRemove) {
	playerScore -= scoreToRemove;
	return;
}

bool Scores::hasThePlayerLost() {
	if (enemyScore > playerScore) {
		return true;
	} else {
		return false;
	}
}

sf::Vector2f Scores::getPosition() {
	return sprite_.getPosition();
}

sf::FloatRect Scores::getCollisionRect() {
	return sf::FloatRect(sprite_.getPosition().x, sprite_.getPosition().y, 1, 1);
}

void Scores::draw() {
	GAME.getRenderWindow().draw(sprite_);
	GAME.getRenderWindow().draw(text_);
	return;
}

void Scores::update(sf::Time& elapsed) {
	std::stringstream stream;
	stream << "Blue: " << playerScore << "   Red: " << enemyScore;

	text_.setString(stream.str());
	return;
}