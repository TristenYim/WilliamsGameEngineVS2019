#include "GameScene.h"
#include "Ship.h"

GameScene::GameScene() {
	ShipPtr ship = std::make_shared<Ship> (192, 880);
	ShipPtr ship2 = std::make_shared<Ship>(192, 200);
	addGameObject(ship);
	addGameObject(ship2);
}
