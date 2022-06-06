#include "Tower.h"
#include "Projectile.h"

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
		objectsToAttack.push_back(otherGameObject);
	}
	return;
}

void Tower::attackAction() {
	sprite_.setColor(sf::Color::Green);
	GameObject furthestToTheRight = objectsToAttack[0];
	for (int index = 1; index < objectsToAttack.size(); index++) {
		if (objectsToAttack[index].getPosition().x >= furthestToTheRight.getPosition().x) {
			furthestToTheRight = objectsToAttack[index];
		}
	}
	sf::Vector2f distance = sf::Vector2f(furthestToTheRight.getPosition().x - sprite_.getPosition().x, furthestToTheRight.getPosition().y - sprite_.getPosition().y);
	ProjectilePtr projectile_ = std::make_shared<Projectile>(sprite_.getPosition(), distance, 0.05);
	GAME.getCurrentScene().addGameObject(projectile_);
	objectsToAttack.clear();
	return;
}