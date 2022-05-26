#include "OffenseBot.h"
#include "PlayingField.h"
#include <fstream>

OffenseBot::OffenseBot(sf::Vector2f ipos, float imovementSpeed, bool spawnOnBottom) {
	sprite_.setTexture(GAME.getTexture("Resources/Blue Square.png"));

	// The position in modified to spawn the offense bot on the corner of a square. Since this constructor cannot access the playing field, it must take an absolute position input rather than a relative one
	sprite_.setPosition(sf::Vector2f(ipos.x - sprite_.getGlobalBounds().width / 2.0, ipos.y - sprite_.getGlobalBounds().height / 2.0));
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

// TODO: Make the pathing less susceptible to phasing

void OffenseBot::update(sf::Time& elapsed) {
	float distance = movementSpeed * elapsed.asMilliseconds();
	sf::Vector2f neoPosition = sprite_.getPosition();
	sf::Vector2f positionToReach = sprite_.getPosition();
	sf::Vector2i relativeNeoPosition = PlayingField::findRelativePosition(neoPosition);

	while (distance > 0) {
		int xMovementIncrement = 0;
		int xCheckIncrement = 0;
		int yMovementIncrement = 0;
		int yCheckIncrement = 0;

		switch (directions[currentOperation]) {
		case GoUp:
			yMovementIncrement = -1;
			yCheckIncrement = -2;
			break;
		case GoLeft:
			xMovementIncrement = -1;
			xCheckIncrement = -2;
			break;
		case GoDown:
			yMovementIncrement = 1;
			yCheckIncrement = 1;
			break;
		case GoRight:
			xMovementIncrement = 1;
			xCheckIncrement = 1;
			break;
		}

		relativeNeoPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width + (int)(xCheckIncrement / 2) * distance, neoPosition.y + sprite_.getGlobalBounds().height + (int)(yCheckIncrement / 2) * distance));
		positionToReach.x += xMovementIncrement * distance;
		positionToReach.y += yMovementIncrement * distance;
		while (relativeNeoPosition != PlayingField::findRelativePosition(positionToReach) && PlayingField::canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x + xCheckIncrement, relativeNeoPosition.y + yCheckIncrement), OFFENSE_TAG)) {
			relativeNeoPosition.x += xMovementIncrement;
			relativeNeoPosition.y += yMovementIncrement;
		}

		if (relativeNeoPosition == PlayingField::findRelativePosition(positionToReach)) {
			neoPosition = positionToReach;
		} else {
			distance -= std::abs(xMovementIncrement * (neoPosition.x - PlayingField::findAbsoluteXPosition(relativeNeoPosition.x))) - std::abs(yMovmentIncrement * (neoPosition.y - PlayingField::findAbsoluteYPosition(relativeNeoPosition.y)));
			neoPosition = PlayingField::findAbsoluteValue(sf::Vector2f(relativeNeoPosition.x - xMovementIncrement, relativeNeoPosition.y - yMovementIncrement));
			currentOperation++;
	}
	sprite_.setPosition(neoPosition);
}

void OffenseBot::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}
