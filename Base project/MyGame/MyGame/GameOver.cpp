#include "GameOver.h"
#include "GameScene.h"
#include <sstream>

GameOver::GameOver(int score) {
	gameOverText_.setFont(GAME.getFont("Courneuf-Regular.ttf"));
	//TODO: Put the text in the center of the screen
	float windowLength = GAME.getRenderWindow().getSize().x;
	float windowWidth = GAME.getRenderWindow().getSize().y;
	//See above
	gameOverText_.setCharacterSize(108);
	gameOverText_.setColor(sf::Color::Red);
	std::stringstream stream_;
	stream_ << "GAME OVER!\n\nScore: " << score;
	gameOverText_.setString(stream_.str());
	assignTag("gameover");
}

void GameOver::draw() {
	GAME.getRenderWindow().draw(gameOverText_);
	return;
}

void GameOver::update(sf::Time& elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

		return;
	}
}