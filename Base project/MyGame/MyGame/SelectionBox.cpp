#include "SelectionBox.h"

SelectionBox::SelectionBox(sf::Vector2f ipos) {
	sprite_.setPosition(ipos);
	sprite_.setTexture(GAME.getTexture("Resources/Selection Box.png"));
	setCollisionCheckEnabled(true);
	assignTag("selection");
}

void SelectionBox::addToPosition(sf::Vector2f additive) {
	sf::Vector2f neoPos = sprite_.getPosition();
	neoPos.x += additive.x;
	neoPos.y += additive.y;
	sprite_.setPosition(neoPos);
	return;
}

sf::Vector2f SelectionBox::getPosition() {
	return sprite_.getPosition();
}

void SelectionBox::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect SelectionBox::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void SelectionBox::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("obstacle")) {
		sprite_.setColor(sf::Color(0, 95, 168, 255));
	} else {
		sprite_.setColor(sf::Color(226, 12, 16, 255));
	}
	return;
}