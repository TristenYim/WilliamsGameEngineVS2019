#include "Laser.h"

Laser::Laser(sf::Vector2f ipos, float ispeed) {
	sprite_.setTexture(GAME.getTexture("Resources/laser.png"));
	sprite_.setPosition(ipos);
	assignTag("laser");
	speed = ispeed;
}

void Laser::draw() {
	GAME.getRenderWindow().draw(sprite_);
}

void Laser::update(sf::Time& elapsed) {
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x > GAME.getRenderWindow().getSize().x) {
		makeDead();
	} else {
		sprite_.setPosition(sf::Vector2f(pos.x + speed * msElapsed, pos.y));
	}
}