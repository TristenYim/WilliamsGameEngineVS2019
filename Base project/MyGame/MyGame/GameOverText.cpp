#include "GameOverText.h"
#include "GameScene.h"
#include <sstream>

GameOverText::GameOverText() {
	setupText(sf::Vector2f(GAME.getRenderWindow().getSize().x / 2.0, GAME.getRenderWindow().getSize().y / 2.0), 118, sf::Color::Red);

	std::stringstream stream_;
	stream_ << "GAME OVER!\n\n" << "Press \'ENTER\' to restart!";
	text_.setString(stream_.str());

	text_.setOrigin(text_.getGlobalBounds().width / 2.0, text_.getGlobalBounds().height / 2.0);

	assignTag("gameovertext");
}

void GameOverText::update(sf::Time& elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		GameScenePtr neoScene = std::make_shared<GameScene>();
		GAME.setScene(neoScene);
		return;
	}
}