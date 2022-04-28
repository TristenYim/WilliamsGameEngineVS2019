#include "GameOverScene.h"
#include "GameOver.h"

GameOverScene::GameOverScene(int score) {
	GameOverPtr gameOver_ = std::make_shared<GameOver>(score);
	addGameObject(gameOver_);
}