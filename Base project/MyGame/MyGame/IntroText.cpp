#include "IntroText.h"
#include "GameScene.h"
#include <fstream>
#include <sstream>

IntroText::IntroText(sf::Vector2f ipos, int icharSize, sf::Color itextColor) {
	setupText(ipos, icharSize, itextColor);

	std::string temp;
	std::string introTextString;
	std::ifstream introTextInput;
	introTextInput.open("Intro.txt");
	while (getline(introTextInput, temp)) {
		introTextString += temp + "\n";
	}
	introTextInput.close();
	
	std::stringstream stream_;
	stream_ << introTextString << "\n\n" << "Press \'ENTER\' to continue!";
	text_.setString(stream_.str());

	text_.setOrigin(text_.getGlobalBounds().width / 2.0, text_.getGlobalBounds().height / 2.0);
	text_.setPosition(ipos);

	assignTag("intro");
}

void IntroText::update(sf::Time& elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		GameScenePtr neoScene = std::make_shared<GameScene>();
		GAME.setScene(neoScene);
		return;
	}
}