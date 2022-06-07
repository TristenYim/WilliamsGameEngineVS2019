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
	attackTimer -= elapsed.asMilliseconds();
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
		if (0 >= attackTimer) {
			attackTimer = attackDelay;
			attackAction(otherGameObject);
		}
	}
	return;
}

void Tower::attackAction(GameObject botToAttack) {
	sf::Vector2f distance = sf::Vector2f(botToAttack.getPosition().x - sprite_.getPosition().x, botToAttack.getPosition().y - sprite_.getPosition().y);
	ProjectilePtr projectile_ = std::make_shared<Projectile>(sf::Vector2f(sprite_.getPosition()), distance, 1.0);
	GAME.getCurrentScene().addGameObject(projectile_);
	return;
}