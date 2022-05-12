#include "Tower.h"

Tower::Tower(sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Purple Square.png"));
	sprite_.setPosition(ipos);
	assignTag("tower");
}

//void Tower::update(sf::Time& elapsed) {
//	if (objectInRange) {
//		attackTimer -= elapsed.asMilliseconds();
//		if (0 >= attackTimer) {
//			attackAction();
//			attackTimer = attackDelay;
//		}
//	} else if (attackDelay != attackTimer) {
//		attackTimer = attackDelay;
//	}
//	return;
//}

void Tower::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}