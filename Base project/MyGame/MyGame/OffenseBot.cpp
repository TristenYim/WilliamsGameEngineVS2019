#include "OffenseBot.h"
#include "PlayingField.h"

OffenseBot::OffenseBot(sf::Vector2f ipos, float imovementSpeed) {
	sprite_.setTexture(GAME.getTexture("Resources/Blue Square.png"));

	// The position in modified to spawn the offense bot on the corner of a square. Since this constructor cannot access the playing field, it must take an absolute position input rather than a relative one
	sprite_.setPosition(sf::Vector2f(ipos.x - sprite_.getGlobalBounds().width / 2.0, ipos.y - sprite_.getGlobalBounds().height / 2.0));
	movementSpeed = imovementSpeed;
	assignTag(OFFENSE_TAG);
}

void OffenseBot::update(sf::Time& elapsed) {
	float distance = movementSpeed * elapsed.asMilliseconds();
	sf::Vector2f neoPosition = sprite_.getPosition();
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
		if (PlayingField::canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x + xCheckIncrement, relativeNeoPosition.y + yCheckIncrement), OFFENSE_TAG)) {
			neoPosition.x += xMovementIncrement * distance;
			neoPosition.y += yMovementIncrement * distance;
			distance = 0;
		} else {
			while (!PlayingField::canThisObjectBeAt(relativeNeoPosition, OFFENSE_TAG)) {
				relativeNeoPosition.x += xMovementIncrement;
				relativeNeoPosition.y += yMovementIncrement;
			}

			neoPosition = sf::Vector2f(PlayingField::findAbsolutePosition(relativeNeoPosition).x - sprite_.getGlobalBounds().width / 2.0, PlayingField::findAbsolutePosition(relativeNeoPosition).y - sprite_.getGlobalBounds().height / 2.0);
			distance -= (int)(xCheckIncrement / 2) * (neoPosition.x - sprite_.getPosition().x) + (int)(yCheckIncrement / 2) * (neoPosition.y - sprite_.getPosition().y);

			if (!PlayingField::canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x + xCheckIncrement, relativeNeoPosition.y + yCheckIncrement), OFFENSE_TAG)) {
				currentOperation++;
			}
		}
	}
	sprite_.setPosition(neoPosition);
}

void OffenseBot::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}