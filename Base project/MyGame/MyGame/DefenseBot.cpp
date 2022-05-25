#include "DefenseBot.h"
#include "PlayingField.h"

DefenseBot::DefenseBot(sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Orange Square.png"));
	sprite_.setPosition(ipos);
	assignTag(DEFENSE_TAG);
}

void DefenseBot::update(sf::Time& elapsed) {
	sf::Vector2f neoPosition = sprite_.getPosition();

	// The locations of two corners are used to ensure the defense bot can't drive partially into obstacles at weird angles
	sf::Vector2i relativeNeoCornerPosition;
	sf::Vector2i relativeNeoCornerPosition2;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		neoPosition.y -= DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = PlayingField::findRelativePosition(neoPosition);
		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
			relativeNeoCornerPosition.y++;
			relativeNeoCornerPosition2.y++;
			if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.y) {
				neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
				break;
			}
		}
		if (PlayingField::findRelativePosition(neoPosition).y != relativeNeoCornerPosition.y && OUTSIDE_OF_FIELD_UP_OR_LEFT != relativeNeoCornerPosition.y) {
			neoPosition.y = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).y;
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		neoPosition.y += DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height));
		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y + sprite_.getGlobalBounds().height));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its y-coordinate accordingly
		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
			relativeNeoCornerPosition.y--;
			relativeNeoCornerPosition2.y--;
			if (relativeNeoCornerPosition.y == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
				break;
			}
		}
		if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height)).y != relativeNeoCornerPosition.y && relativeNeoCornerPosition.y != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
			neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x, relativeNeoCornerPosition.y + 1)).y - sprite_.getGlobalBounds().height;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		neoPosition.x -= DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = PlayingField::findRelativePosition(neoPosition);
		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height - 1));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
			relativeNeoCornerPosition.x++;
			relativeNeoCornerPosition2.x++;
			if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
				neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
				break;
			}
		}
		if (PlayingField::findRelativePosition(neoPosition).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
			neoPosition.x = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).x;
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		neoPosition.x += DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y));
		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height - 1));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
			relativeNeoCornerPosition.x--;
			relativeNeoCornerPosition2.x--;
			if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
				break;
			}
		}
		if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y)).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
			neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x + 1, relativeNeoCornerPosition.y)).x - sprite_.getGlobalBounds().width;
		}
	}

	sf::Vector2i relativePosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height));
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x) {
		neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
	}
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y) {
		neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
	}

	relativePosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y));
	if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x) {
		neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
	}
	if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
		neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
	}

	sprite_.setPosition(neoPosition);
	return;
}

sf::FloatRect DefenseBot::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void DefenseBot::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}