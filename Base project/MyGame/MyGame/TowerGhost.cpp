#include "TowerGhost.h"

TowerGhost::TowerGhost(sf::Vector2f ipos, sf::Texture texture_) {
	sprite_.setTexture(texture_);
	sprite_.setPosition(ipos);
	assignTag("ghost");
}

void TowerGhost::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}