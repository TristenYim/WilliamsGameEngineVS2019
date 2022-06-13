#include "EndingScene.h"
#include "EndingText.h"

EndingScene::EndingScene(bool didThePlayerWin) {
	EndingTextPtr endingText_;
	if (didThePlayerWin) {
		endingText_ = std::make_shared<EndingText>("YOU WIN!", sf::Color::Green);
	} else {
		endingText_ = std::make_shared<EndingText>("GAME OVER!", sf::Color::Red);
	}
	addGameObject(endingText_);
}