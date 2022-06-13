#include "Tower.h"
#include "Projectile.h"
#define _USE_MATH_DEFINES
#include <math.h>

Tower::Tower(sf::Vector2f ipos, float irange, float iattackDelay, float iprojectileSpeed, float irotationSpeed) {
	sprite_.setTexture(GAME.getTexture("Resources/Purple Square.png"));
	sprite_.setPosition(ipos);
	sprite_.setOrigin(sf::Vector2f(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0));

	setCollisionCheckEnabled(true);
	assignTag("tower");
	range = irange;
	attackDelay = iattackDelay;
	projectileSpeed = iprojectileSpeed;
	rotationSpeed = irotationSpeed;
}

Tower::Tower(TowerTypes itype, sf::Vector2f ipos) {
	sprite_.setPosition(ipos);
	sprite_.setOrigin(sf::Vector2f(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0));
	setCollisionCheckEnabled(true);

	switch (itype)
	{
	case CheesyPoofs:
		sprite_.setTexture(GAME.getTexture("Resources/Tower 254.png"));
		range = 254;
		attackDelay = 400;
		rotationSpeed = 0.3;
		projectile_ = std::make_shared<Projectile>(sf::Vector2f(sprite_.getPosition()), "Resources/Cheesy Poof.png", 0, 0.8, 50);
		break;
	}

	assignTag("tower");
}

void Tower::update(sf::Time& elapsed) {
	attackTimer -= elapsed.asMilliseconds();
	if (!objectToTarget.empty()) {
		targetEnemy(elapsed.asMilliseconds());
	}
	objectToTarget.clear();
	return;
}

sf::FloatRect Tower::getCollisionRect() {
	return sf::FloatRect(sf::Vector2f(sprite_.getPosition().x - range / 2.0, sprite_.getPosition().y - range / 2.0), sf::Vector2f(range, range));
}

void Tower::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

void Tower::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("offense") && objectToTarget.empty()) {
		objectToTarget.push_back(otherGameObject);
	}
	return;
}

void Tower::targetEnemy(float msElapsed) {
	sf::Vector2f distanceToEnemy = sf::Vector2f(objectToTarget[0].getPosition().x - sprite_.getPosition().x, objectToTarget[0].getPosition().y - sprite_.getPosition().y);

	float rotationToReach = 180 * atan(distanceToEnemy.y / distanceToEnemy.x) / M_PI;
	float currentRotation = sprite_.getRotation();
	if (distanceToEnemy.x > 0) {
		if (0 <= rotationToReach) {
			rotationToReach = 180 + rotationToReach;
		} else {
			rotationToReach = -180 + rotationToReach;
		}
	}
	while (0 > rotationToReach) {
		rotationToReach += 360;
	}

	if ((int)currentRotation != (int)rotationToReach) {
		if ((rotationToReach - currentRotation <= 180.0 && rotationToReach - currentRotation >= 0.0) || rotationToReach - currentRotation < -180) {
			currentRotation += msElapsed * rotationSpeed;
			if (currentRotation > rotationToReach && rotationToReach - currentRotation > 0) {
				currentRotation = rotationToReach;
			}
		} else {
			currentRotation -= msElapsed * rotationSpeed;
			if (currentRotation < rotationToReach && rotationToReach - currentRotation < 0) {
				currentRotation = rotationToReach;
			}
		}
		sprite_.setRotation(currentRotation);
	}

	if ((int)(rotationToReach) == (int)currentRotation && 0 >= attackTimer) {
		attackAction(distanceToEnemy);
	}
	return;
}

void Tower::attackAction(sf::Vector2f distanceToEnemy) {
	attackTimer = attackDelay;
	projectile_->set
	ProjectilePtr projectile_ = std::make_shared<Projectile>();
	GAME.getCurrentScene().addGameObject(projectile_);
	return;
}