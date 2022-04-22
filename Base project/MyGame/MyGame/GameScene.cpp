#include "GameScene.h"
#include "Ship.h"
#include "Cookie.h"
#include "CookieSpawner.h"
#include "ScoreText.h"

GameScene::GameScene() {
	std::vector<Gun> shipGuns = { Gun(500, 1.0f, 0.25), Gun(300, 2.0f, 0.5), Gun(500, 1.0f, 0.75) };
	std::vector<Gun> ship2Guns = { Gun(150, 2.0f, 0.5) };
	ShipPtr ship_ = std::make_shared<Ship>(sf::Vector2f{ 192, 880 }, shipGuns, true, true);
	ShipPtr ship_2 = std::make_shared<Ship>(sf::Vector2f{ 192, 200 }, ship2Guns, false, true);
	CookieSpawnerPtr cookieSpawner_ = std::make_shared<CookieSpawner>(100, sf::Vector2i(150, 50));
	ScoreTextPtr scoreText_ = std::make_shared<ScoreText>(sf::Vector2f(100, 100), 32, sf::Color(255, 255, 255, 255));
	addGameObject(ship_);
	addGameObject(ship_2);
	addGameObject(cookieSpawner_);
	addGameObject(scoreText_);
}

int GameScene::getScore() {
	return score_;
}

void GameScene::increaseScore() {
	score_++;
	return;
}

void GameScene::increaseScore(int additive) {
	score_ += additive;
	return;
}