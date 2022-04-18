#pragma once
#include "Engine/GameEngine.h"

const float SPEED = 0.3f;

class Ship : public GameObject {
public:
	//Creates are ship. Automatically starts it at 192, 504, or you can specify a custom location for it to start at.
	Ship();
	Ship(int x, int y);
	//Game Object methods
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<Ship> ShipPtr;