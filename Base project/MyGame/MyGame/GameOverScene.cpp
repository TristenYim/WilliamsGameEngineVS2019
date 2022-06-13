#include "GameOverScene.h"
#include "GameOverText.h"

GameOverScene::GameOverScene() {
	GameOverTextPtr gameOverText_ = std::make_shared<GameOverText>();
	addGameObject(gameOverText_);
}