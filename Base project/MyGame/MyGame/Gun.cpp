#include "Gun.h"
#include "Laser.h"

Gun::Gun(int ifireDelay, float ilaserSpeed, float iposition) {
	fireDelay = ifireDelay;
	laserSpeed = ilaserSpeed;
	positionOnShip = iposition;
}

void Gun::updateGun(int msElapsed) {
	if (0 < fireTimer) {
		fireTimer -= msElapsed;
	}
	return;
}

void Gun::attemptToShoot(sf::Vector2f shipPos, sf::Vector2f shipBounds) {
	if (0 >= fireTimer) {
		fireTimer = fireDelay;
		float ilaserX = shipPos.x + shipBounds.x;
		float ilaserY = shipPos.y + (shipBounds.y * positionOnShip);
		LaserPtr laserToAdd = std::make_shared<Laser>(sf::Vector2f(ilaserX, ilaserY), laserSpeed);
		GAME.getCurrentScene().addGameObject(laserToAdd);
	}
	return;
}