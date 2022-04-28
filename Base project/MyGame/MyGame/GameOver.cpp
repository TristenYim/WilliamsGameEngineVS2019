#include "GameOver.h"
#include "GameScene.h"
#include <sstream>

GameOver::GameOver(int score) {
	float windowLength = GAME.getRenderWindow().getSize().x;
	float windowHeight = GAME.getRenderWindow().getSize().y;
	setupText(sf::Vector2f(windowLength / 2.0, windowHeight / 2.0), 108, sf::Color::Red);
	std::stringstream stream_;
	stream_ << "GAME OVER!\n\nScore: " << score;
	text_.setString(stream_.str());
	assignTag("gameover");
}

void GameOver::update(sf::Time& elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		GameScenePtr neoScene = std::make_shared<GameScene>();
		GAME.setScene(neoScene);
		return;
	}
}