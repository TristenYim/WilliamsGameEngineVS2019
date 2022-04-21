#pragma once
#include "Engine/GameEngine.h"
#include "Gun.h"

const float SPEED = 0.6f;

class Ship : public GameObject {
public:
	//Creates are ship. Automatically starts it at 192, 504, or you can specify a custom location for it to start at.
	Ship();
	Ship(sf::Vector2f ipos, std::vector<Gun> iguns, bool iuseWASDForMovement, bool iholdPrevention);
	//Game Object methods
	void draw();
	void update(sf::Time& elapsed);
private:
	//All of the different guns on the ship
	std::vector<Gun> guns;
	sf::Sprite sprite_;
	//If true, WASD is the movement with Q being the shoot button. If false IJKL is used for movement with U being the shoot button.
	bool useWASDQControls;
	//If true, holding down fire does not fire. The player must press the fire button each time
	bool holdPrevention;
	//Used to ensure the player has to press a key each time they want to attack
	bool isHoldingQ = false;
	bool isHoldingU = false;
};

typedef std::shared_ptr<Ship> ShipPtr;