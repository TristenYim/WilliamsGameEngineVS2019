#pragma once

#include "Engine/GameEngine.h"

//Each gun is a set of variables which state its location on the ship, fire timer, fire delay, and speed of lasers it shoots. They are not game objects, only parts of ships
class Gun {
public:
	//Declares the gun with a set delay, laser speed, and position
	Gun(int ifireDelay, float ilaserSpeed, float iposition);

	//Updates the fire timer of the gun
	void updateGun(int msElapsed);

	//Checks to see if it can shoot. Spawns a laser if it can shoot
	void attemptToShoot(sf::Vector2f shipPos, sf::Vector2f shipBounds);
private:
	int fireTimer = 0;
	int fireDelay;
	float laserSpeed;
	//The position on ship is the fraction of the ship that its y value is that. An input of 0.5 would be halfway up the ship
	float positionOnShip;
};