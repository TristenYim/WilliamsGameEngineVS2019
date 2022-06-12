#include "OffenseBot.h"
#include "PlayingField.h"
#include "Credits.h"
#include <fstream>

OffenseBot::OffenseBot(sf::Vector2f ipos, float imovementSpeed, bool spawnOnBottom) {
	sprite_.setTexture(GAME.getTexture("Resources/Blue Square.png"));

	// The position in modified to spawn the offense bot on the corner of a square. Since this constructor cannot access the playing field, it must take an absolute position input rather than a relative one
	sprite_.setPosition(sf::Vector2f(ipos.x - sprite_.getGlobalBounds().width / 2.0, ipos.y - sprite_.getGlobalBounds().height / 2.0));
	setCollisionCheckEnabled(true);
	movementSpeed = imovementSpeed;

	assignTag(OFFENSE_TAG);
	std::ifstream fieldMapFile;
	fieldMapFile.open(FIELD_MAP_FILE);
	std::string directions_string;
	//getline(fieldMapFile, directions_string);
	for (int index = 0; index <= spawnOnBottom; index++) {
		getline(fieldMapFile, directions_string);
	}
	fieldMapFile.close();
	for (int index = 0; index <= directions_string.size(); index++) {
		switch (directions_string[index]) {
		case 'U':
			directions.push_back(GoUp);
			break;
		case 'L':
			directions.push_back(GoLeft);
			break;
		case 'D':
			directions.push_back(GoDown);
			break;
		case 'R':
			directions.push_back(GoRight);
			break;
		case 'W':
			directions.push_back(Score);
			break;
		}
	}
}

void OffenseBot::update(sf::Time& elapsed) {
	float distance = movementSpeed * elapsed.asMilliseconds();
	sf::Vector2f neoPosition = sprite_.getPosition();
	sf::Vector2f positionToReach = sprite_.getPosition();
	sf::Vector2i relativePositionToCheck;

	while (distance > 0) {
		int xMovementIncrement = 0;
		int xCheckIncrement = 0;
		int yMovementIncrement = 0;
		int yCheckIncrement = 0;

		switch (directions[currentOperation]) {
		case GoUp:
			yMovementIncrement = -1;
			yCheckIncrement = -1;
			break;
		case GoLeft:
			xMovementIncrement = -1;
			xCheckIncrement = -1;
			break;
		case GoDown:
			yMovementIncrement = 1;
			yCheckIncrement = 2;
			break;
		case GoRight:
			xMovementIncrement = 1;
			xCheckIncrement = 2;
			break;
		}

		relativePositionToCheck = PlayingField::findRelativePosition(neoPosition);
		positionToReach.x += xMovementIncrement * distance;
		positionToReach.y += yMovementIncrement * distance;
		while (relativePositionToCheck != PlayingField::findRelativePosition(positionToReach) && PlayingField::canThisObjectBeAt(sf::Vector2i(relativePositionToCheck.x + xCheckIncrement, relativePositionToCheck.y + yCheckIncrement), OFFENSE_TAG)) {
			relativePositionToCheck.x += xMovementIncrement;
			relativePositionToCheck.y += yMovementIncrement;
		}

		if (!PlayingField::canThisObjectBeAt(sf::Vector2i(relativePositionToCheck.x + xCheckIncrement, relativePositionToCheck.y + yCheckIncrement), OFFENSE_TAG)) {
			distance -= std::abs(xMovementIncrement * (neoPosition.x - PlayingField::findAbsoluteXPosition(relativePositionToCheck.x))) + std::abs(yMovementIncrement * (neoPosition.y - PlayingField::findAbsoluteYPosition(relativePositionToCheck.y)));
			neoPosition = sf::Vector2f(PlayingField::findAbsoluteXPosition(relativePositionToCheck.x) + sprite_.getGlobalBounds().width / 2.0, PlayingField::findAbsoluteYPosition(relativePositionToCheck.y) + sprite_.getGlobalBounds().height / 2.0);
			positionToReach = neoPosition;
			currentOperation++;
		} else {
			neoPosition = positionToReach;
			distance = 0;
		}
	}
	sprite_.setPosition(neoPosition);
	return;
}

sf::FloatRect OffenseBot::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void OffenseBot::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

void OffenseBot::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("projectile")) {
		otherGameObject.makeDead();
		makeDead();
		Credits::addCredit(50);
	}
	return;
}

sf::Vector2f OffenseBot::getPosition() {
	return sf::Vector2f(sprite_.getPosition().x + sprite_.getGlobalBounds().width, sprite_.getPosition().y + sprite_.getGlobalBounds().height);
}