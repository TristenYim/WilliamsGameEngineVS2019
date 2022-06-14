#include "TowerGhost.h"
#include "PlayingField.h"

sf::Sprite TowerGhost::sprite_;
sf::Sprite TowerGhost::rangeBox_;
bool TowerGhost::visibility;
TowerTypes TowerGhost::type_;

TowerGhost::TowerGhost() {
	visibility = false;
	assignTag("ghost");
}

void TowerGhost::setPosition(sf::Vector2f(neoPosition)) {
	sprite_.setPosition(neoPosition);
	rangeBox_.setPosition(neoPosition);
	return;
}

void TowerGhost::setVisibility(bool neoVisibility) {
	visibility = neoVisibility;
	return;
}

void TowerGhost::setType(TowerTypes neoType) {
	sf::Vector2f originalPosition = sprite_.getPosition();
	type_ = neoType;
	sprite_ = Tower::getTowerSprite(type_);
	sf::Color neoColor = sprite_.getColor();
	neoColor.a = 200;
	sprite_.setColor(neoColor);
	rangeBox_ = Tower::getTowerRangeSprite(type_);
	rangeBox_.setColor(sf::Color(254, 254, 254, 50));
	sprite_.setPosition(originalPosition);
	rangeBox_.setPosition(originalPosition);
	return;
}

bool TowerGhost::isVisibile() {
	return visibility;
};

TowerTypes TowerGhost::getType() {
	return type_;
}

void TowerGhost::draw() {
	if (visibility && PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(sprite_.getPosition()), "tower")) {
		GAME.getRenderWindow().draw(sprite_);
		GAME.getRenderWindow().draw(rangeBox_);
	}
	return;
}