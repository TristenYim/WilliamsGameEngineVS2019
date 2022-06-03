#include "Tower.h"

Tower::Tower(sf::Vector2f ipos, float irange, float iattackDelay) {
	sprite_.setTexture(GAME.getTexture("Resources/Purple Square.png"));
	sprite_.setPosition(ipos);
	setCollisionCheckEnabled(true);
	getCollisionRect();
	assignTag("tower");
	range = irange;
	attackDelay = iattackDelay;
}

void Tower::update(sf::Time& elapsed) {
	if (objectsToAttack.size() > 0) {
		attackTimer -= elapsed.asMilliseconds();
		if (0 >= attackTimer) {
			attackAction();
			attackTimer = attackDelay;
		}
	} else if (attackDelay != attackTimer) {
		attackTimer = attackDelay;
	}
	return;
}

sf::FloatRect Tower::getCollisionRect() {
	return sf::FloatRect(sprite_.getPosition(), sf::Vector2f(range, range));
}

void Tower::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

void Tower::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("offense")) {
		objectsToAttack.push_back(GameObjectPtr(otherGameObject));
	}
	return;
}

void Tower::attackAction() {
	GameObjectPtr furthestToTheRight = objectsToAttack[0];
	for (int index = 1; index < objectsToAttack.size(); index++) {
		if (objectsToAttack[index].getPosition().x >= furthestToTheRight.getPosition().x) {
			furthestToTheRight = objectsToAttack[index];
		}
	}
	sprite_.setColor(sf::Color::Green);
	furthestToTheRight.makeDead();
}