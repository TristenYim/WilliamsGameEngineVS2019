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
	if (botsInRange.size() > 0) {
		attackTimer -= elapsed.asMilliseconds();
		if (0 >= attackTimer) {
			attackTimer = attackDelay;
			attackAction();
		}
	} else if (attackDelay != attackTimer) {
		attackTimer = attackDelay;
	}
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
		botsInRange.push_back(std::make_shared<GameObject>(otherGameObject));
	}
	return;
}

void Tower::attackAction() {
	sprite_.setColor(sf::Color::Green);

	// To make the game run faster, the tower only checks to see if the offense bots in its list to attack are still in range when it needs to attack
	for (auto& offenseBot_ : botsInRange) {
		if (!sprite_.getGlobalBounds().intersects(offenseBot_->getCollisionRect())) {
			botsInRange.remove((GameObjectPtr)offenseBot_);
		}
	}
	if (botsInRange.size() == 0) {
		attackTimer = 0;
	} else {
		GameObjectPtr botToAttack = botsInRange.front();

		sf::Vector2f distance = sf::Vector2f(botToAttack->getPosition().x - sprite_.getPosition().x, botToAttack->getPosition().y - sprite_.getPosition().y);
		ProjectilePtr projectile_ = std::make_shared<Projectile>(sprite_.getPosition(), distance, 0.5);
		GAME.getCurrentScene().addGameObject(projectile_);
	}
	return;
}