#include "GameScene.h"
#include "Ship.h"

GameScene::GameScene() {
	ShipPtr ship = std::make_shared<Ship>(sf::Vector2f{ 192, 880 }, 200, 1.2f, true);
	ShipPtr ship2 = std::make_shared<Ship>(sf::Vector2f{ 192, 200 }, 200, 1.2f, false);
	addGameObject(ship);
	addGameObject(ship2);
}
