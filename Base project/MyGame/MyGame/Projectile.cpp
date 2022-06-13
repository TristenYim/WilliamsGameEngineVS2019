#include "Projectile.h"
#include "OffenseBot.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "PlayingField.h"

Projectile::Projectile(sf::Vector2f ipos, sf::Vector2f distanceFromEnemy, float speed, int idamage) {
	sprite_.setTexture(GAME.getTexture("Resources/Yellow Square.png"));
	sprite_.setPosition(ipos);
	sprite_.setOrigin(sf::Vector2f(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0));

	damage = idamage;

	float rotation = atan(distanceFromEnemy.y / distanceFromEnemy.x);
	sprite_.setRotation(180 / M_PI * rotation);
	float speedAdjustmentMultiplier = speed / sqrt(distanceFromEnemy.x * distanceFromEnemy.x + distanceFromEnemy.y * distanceFromEnemy.y);
	directionalSpeed.x = distanceFromEnemy.x * speedAdjustmentMultiplier;
	directionalSpeed.y = distanceFromEnemy.y * speedAdjustmentMultiplier;

	setCollisionCheckEnabled(true);
	assignTag("projectile");
}

int Projectile::getDamage() {
	return damage;
}

void Projectile::update(sf::Time& elapsed) {
	sprite_.move(sf::Vector2f(directionalSpeed.x * elapsed.asMilliseconds(), directionalSpeed.y * elapsed.asMilliseconds()));
	sf::Vector2i relativePosition = PlayingField::findRelativePosition(sprite_.getPosition());
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x || OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x || OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y || OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
		makeDead();
	}
	return;
}

void Projectile::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect Projectile::getCollisionRect() {
	return sprite_.getGlobalBounds();
}