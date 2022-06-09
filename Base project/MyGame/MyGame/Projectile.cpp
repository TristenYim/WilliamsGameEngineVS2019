#include "Projectile.h"
#include "OffenseBot.h"
#define _USE_MATH_DEFINES
#include <math.h>

//TODO: Fix it so it detects the angle

Projectile::Projectile(sf::Vector2f ipos, sf::Vector2f distanceFromEnemy, float speed) {
	sprite_.setTexture(GAME.getTexture("Resources/Yellow Square.png"));
	sprite_.setPosition(ipos);
	sprite_.setOrigin(sf::Vector2f(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0));

	float rotation = atan(distanceFromEnemy.y / distanceFromEnemy.x);
	sprite_.setRotation(180 / M_PI * rotation);
	float scalar = speed / sqrt(distanceFromEnemy.x*distanceFromEnemy.x + distanceFromEnemy.y*distanceFromEnemy.y);
	directionalSpeed.x = distanceFromEnemy.x * scalar;
	directionalSpeed.y = distanceFromEnemy.y * scalar;

	setCollisionCheckEnabled(true);
	assignTag("projectile");
}

void Projectile::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect Projectile::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void Projectile::update(sf::Time& elapsed) {
	sprite_.move(sf::Vector2f(directionalSpeed.x * elapsed.asMilliseconds(), directionalSpeed.y * elapsed.asMilliseconds()));
	return;
}

void Projectile::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag(OFFENSE_TAG)) {
		//otherGameObject.makeDead();
		//makeDead();
	}
	return;
}