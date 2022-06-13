#include "EndingText.h"
#include "GameScene.h"
#include <sstream>

EndingText::EndingText(std::string message, sf::Color textColor) {
	setupText(sf::Vector2f(GAME.getRenderWindow().getSize().x / 2.0, GAME.getRenderWindow().getSize().y / 2.0), 118, textColor);

	std::stringstream stream_;
	stream_ << message << "\n\n" << "Press \'ENTER\' to restart!";
	text_.setString(stream_.str());

	text_.setOrigin(text_.getGlobalBounds().width / 2.0, text_.getGlobalBounds().height / 2.0);

	assignTag("endingtext");
}

void EndingText::update(sf::Time& elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		GameScenePtr neoScene = std::make_shared<GameScene>();
		GAME.setScene(neoScene);
		return;
	}
}