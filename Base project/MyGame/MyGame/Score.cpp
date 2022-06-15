#include "Score.h"
#include "EndingScene.h"
#include <sstream>

int Scores::playerScore;
int Scores::enemyScore;
sf::Sprite Scores::sprite_;
float Scores::penaltyOnScreenTimer;
int Scores::penaltyOnScreenDelay;

Scores::Scores(sf::Vector2f pos, int charSize, sf::Color textColor, int iplayerScore, sf::Vector2f ipos, int ipenaltyOnScreenDelay) {
	sprite_.setTexture(GAME.getTexture("Resources/Goal.png"));
	sprite_.setOrigin(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0);
	sprite_.setPosition(ipos);
	setCollisionCheckEnabled(true);

	setupText(pos, charSize, textColor);
	playerScore = iplayerScore;
	enemyScore = 0;
	originalColor = textColor;
	penaltyOnScreenDelay = ipenaltyOnScreenDelay;

	assignTag("scoreobject");
}

void Scores::addEnemyScore(int scoreToAdd) {
	enemyScore += scoreToAdd;
	checkForLosing();
	return;
}

void Scores::majorPenalty() {
	playerScore -= 10;
	checkForLosing();
	penaltyOnScreenTimer = penaltyOnScreenDelay;

	return;
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
	if (0 < penaltyOnScreenTimer) {
		penaltyOnScreenTimer -= elapsed.asMilliseconds();
		std::stringstream stream;
		stream << "MAJOR PENALTY!";

		text_.setString(stream.str());
		text_.setFillColor(sf::Color(200, 150, 100));
	} else {
		text_.setFillColor(originalColor);
		std::stringstream stream;
		stream << "Blue: " << playerScore << "   Red: " << enemyScore;

		text_.setString(stream.str());
	}
	return;
}

void Scores::checkForLosing() {
	if (enemyScore > playerScore) {
		EndingScenePtr neoScene_ = std::make_shared<EndingScene>(false);
		GAME.setScene(neoScene_);
	}
	return;
}