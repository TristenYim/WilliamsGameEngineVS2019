#pragma once
#include "Engine/GameEngine.h"

class Ship : public GameObject {
public:
	Ship();
	Ship(int x, int y);
	void draw();
private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<Ship> ShipPtr;