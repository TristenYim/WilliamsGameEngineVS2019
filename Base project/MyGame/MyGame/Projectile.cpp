#include "Projectile.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "PlayingField.h"

Projectile::Projectile(sf::Vector2f ipos, std::string itexture, sf::Vector2f distanceFromEnemy, float speed, int idamage, bool ipierces) {
	setup(ipos, itexture, distanceFromEnemy, speed, idamage, ipierces);
}

int Projectile::getDamage() {
	return damage;
}

bool Projectile::doesItPierce() {
	return pierces;
}

void Projectile::update(sf::Time& elapsed) {
	updateSpritePosition(elapsed.asMilliseconds());
	return;
}

void Projectile::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect Projectile::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void Projectile::setup(sf::Vector2f ipos, std::string itexture, sf::Vector2f distanceFromEnemy, float speed, int idamage, bool ipierces) {
	sprite_.setTexture(GAME.getTexture(itexture));
	sprite_.setPosition(ipos);
	sprite_.setOrigin(sf::Vector2f(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0));

	float rotation = atan(distanceFromEnemy.y / distanceFromEnemy.x) * 180 / M_PI;
	float currentRotation = sprite_.getRotation();
	if (distanceFromEnemy.x > 0) {
		if (0 <= rotation) {
			rotation = 180 + rotation;
		} else {
			rotation = -180 + rotation;
		}
	}
	sprite_.setRotation(rotation);

	float speedAdjustmentMultiplier = speed / sqrt(distanceFromEnemy.x * distanceFromEnemy.x + distanceFromEnemy.y * distanceFromEnemy.y);
	directionalSpeed.x = distanceFromEnemy.x * speedAdjustmentMultiplier;
	directionalSpeed.y = distanceFromEnemy.y * speedAdjustmentMultiplier;

	damage = idamage;
	pierces = ipierces;

	setCollisionCheckEnabled(true);
	assignTag("projectile");
	return;
}

void Projectile::updateSpritePosition(float msElapesd) {
	sprite_.move(sf::Vector2f(directionalSpeed.x * msElapesd, directionalSpeed.y * msElapesd));
	sf::Vector2i relativePosition = PlayingField::findRelativePosition(sprite_.getPosition());
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x || OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x || OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y || OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
		makeDead();
	}
	return;
}