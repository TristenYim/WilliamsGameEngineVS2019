#pragma once
#include "Engine/GameEngine.h"

const float SPEED = 0.6f;

class Ship : public GameObject {
public:
	//Creates are ship. Automatically starts it at 192, 504, or you can specify a custom location for it to start at.
	Ship();
	Ship(sf::Vector2f ipos, int ifireDelay, float ilaserSpeed, bool iuseWASDForMovement);
	//Game Object methods
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Sprite sprite_;
	int fireTimer_ = 0;
	int fireDelay;
	float laserSpeed;
	//If true, WASD is the movement with Q being the shoot button. If false IJKL is used for movement with U being the shoot button.
	bool useWASDForMovement;
};

typedef std::shared_ptr<Ship> ShipPtr;