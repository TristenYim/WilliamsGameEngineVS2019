#include "OffenseBot.h"

OffenseBot::OffenseBot(sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Orange Square"));
	sprite_.setPosition(ipos);
	assignTag("offense");
}

void OffenseBot::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}