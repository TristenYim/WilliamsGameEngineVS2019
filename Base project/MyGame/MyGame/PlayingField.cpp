#include "PlayingField.h"

const int GRID_SIDE_LENGTH = 32;

PlayingField::PlayingField() {
	sprite_.setTexture(GAME.getTexture("Resources/Field Boundary.png"));
	sprite_.scale(2.0f, 2.0f);
	
	// Sets the x and y to ensure the object is in the center of the screen

	float iposx = GAME.getRenderWindow().getSize().x / 2.0f - sprite_.getTextureRect().width;
	float iposy = GAME.getRenderWindow().getSize().y / 2.0f - sprite_.getTextureRect().height;

	sprite_.setPosition(sf::Vector2f(iposx, iposy));
	assignTag("field");
}

void PlayingField::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::Vector2f PlayingField::findAbsolutePositionOfObject(sf::Vector2i positionInGrid) {

	// Sets the x and y to the corner of the playing field

	float iposx = GAME.getRenderWindow().getSize().x / 2.0f - sprite_.getTextureRect().width;
	float iposy = GAME.getRenderWindow().getSize().y / 2.0f - sprite_.getTextureRect().height;

	// Sets the position in the grid

	iposx += positionInGrid.x * GRID_SIDE_LENGTH;
	iposy += positionInGrid.y * GRID_SIDE_LENGTH;

	return sf::Vector2f(iposx, iposy);
}

void PlayingField::addObstacle()