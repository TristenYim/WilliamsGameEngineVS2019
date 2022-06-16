#include "IntroScene.h"
#include "IntroText.h"
#include <fstream>

IntroScene::IntroScene() {
	IntroTextPtr introText_ = std::make_shared<IntroText>(sf::Vector2f(GAME.getRenderWindow().getSize().x / 2.0, GAME.getRenderWindow().getSize().y / 2.0), 24, sf::Color::White);
	addGameObject(introText_);
}