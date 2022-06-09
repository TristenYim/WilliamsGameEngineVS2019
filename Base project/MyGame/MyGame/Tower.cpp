#include "Tower.h"
#include "Projectile.h"
#define _USE_MATH_DEFINES
#include <math.h>

Tower::Tower(sf::Vector2f ipos, float irange, float iattackDelay, float iprojectileSpeed) {
	sprite_.setTexture(GAME.getTexture("Resources/Purple Square.png"));
	sprite_.setPosition(ipos);
	sprite_.setOrigin(sf::Vector2f(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0));
	setCollisionCheckEnabled(true);
	getCollisionRect();
	assignTag("tower");
	range = irange;
	attackDelay = iattackDelay;
	projectileSpeed = iprojectileSpeed;
}

void Tower::update(sf::Time& elapsed) {
	attackTimer -= elapsed.asMilliseconds();
	if (!objectToTarget.empty()) {
		sf::Vector2f distanceToEnemy = sf::Vector2f(objectToTarget[0].getPosition().x - sprite_.getPosition().x, objectToTarget[0].getPosition().y - sprite_.getPosition().y);
		float rotationToReach = 180 / M_PI * atan(distanceToEnemy.y / distanceToEnemy.x);
		float currentRotation = sprite_.getRotation();
		if (180 <= currentRotation && 360 >= currentRotation) {
			currentRotation = -(currentRotation - 180);
		}
		if ((int)currentRotation != (int)rotationToReach) {
			if ((0 <= currentRotation && 0 <= rotationToReach) || (0 >= currentRotation && 0 >= rotationToReach) || eugc(0 <= currentRotation && 0 >= rotationToReach && 180 >= (540 + rotationToReach - currentRotation))) {
				currentRotation += elapsed.asMilliseconds() * rotationSpeed;
				if (180 <= currentRotation && 360 >= currentRotation) {
					currentRotation = -(currentRotation - 180);
				} else if (currentRotation > 360) {
					currentRotation -= 360;
				}
				//if (currentRotation > rotationToReach) {
				//	currentRotation = rotationToReach;
				//}
			} else {
				currentRotation -= elapsed.asMilliseconds() * rotationSpeed;
				//if (currentRotation < rotationToReach) {
				//	currentRotation = rotationToReach;
				//}
			}
			if (distanceToEnemy.x <= 0) {
				sprite_.setRotation(currentRotation);
			} else {
				sprite_.setRotation(180 + currentRotation);
			}
		}
		if ((int)(rotationToReach) == (int)currentRotation && 0 >= attackTimer) {
			attackAction(distanceToEnemy);
		}
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
	if (otherGameObject.hasTag("offense")) {
		objectToTarget.push_back(otherGameObject);
	}
	return;
}

void Tower::attackAction(sf::Vector2f distanceToEnemy) {
	attackTimer = attackDelay;
	ProjectilePtr projectile_ = std::make_shared<Projectile>(sf::Vector2f(sprite_.getPosition()), distanceToEnemy, projectileSpeed);
	GAME.getCurrentScene().addGameObject(projectile_);
	return;
}