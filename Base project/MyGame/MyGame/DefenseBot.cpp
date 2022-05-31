#include "DefenseBot.h"
#include "PlayingField.h"

DefenseBot::DefenseBot(sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Orange Square.png"));
	sprite_.setPosition(ipos);
	assignTag(DEFENSE_TAG);
}

//void DefenseBot::update(sf::Time& elapsed) {
//	sf::Vector2f neoPosition = sprite_.getPosition();
//
//	// The locations of two corners are used to ensure the defense bot can't drive partially into obstacles at weird angles
//	sf::Vector2i relativeNeoCornerPosition;
//	sf::Vector2i relativeNeoCornerPosition2;
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//		neoPosition.y -= DRIVING_SPEED * elapsed.asMilliseconds();
//		relativeNeoCornerPosition = PlayingField::findRelativePosition(neoPosition);
//		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y));
//
//		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
//		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
//			relativeNeoCornerPosition.y++;
//			relativeNeoCornerPosition2.y++;
//			if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.y) {
//				neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
//				break;
//			}
//		}
//		if (PlayingField::findRelativePosition(neoPosition).y != relativeNeoCornerPosition.y && OUTSIDE_OF_FIELD_UP_OR_LEFT != relativeNeoCornerPosition.y) {
//			neoPosition.y = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).y;
//		}
//	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//		neoPosition.y += DRIVING_SPEED * elapsed.asMilliseconds();
//		relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height));
//		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y + sprite_.getGlobalBounds().height));
//
//		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its y-coordinate accordingly
//		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
//			relativeNeoCornerPosition.y--;
//			relativeNeoCornerPosition2.y--;
//			if (relativeNeoCornerPosition.y == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
//				neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
//				break;
//			}
//		}
//		if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height)).y != relativeNeoCornerPosition.y && relativeNeoCornerPosition.y != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
//			neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x, relativeNeoCornerPosition.y + 1)).y - sprite_.getGlobalBounds().height;
//		}
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//		neoPosition.x -= DRIVING_SPEED * elapsed.asMilliseconds();
//		relativeNeoCornerPosition = PlayingField::findRelativePosition(neoPosition);
//		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height - 1));
//
//		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
//		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
//			relativeNeoCornerPosition.x++;
//			relativeNeoCornerPosition2.x++;
//			if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
//				neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
//				break;
//			}
//		}
//		if (PlayingField::findRelativePosition(neoPosition).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
//			neoPosition.x = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).x;
//		}
//	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//		neoPosition.x += DRIVING_SPEED * elapsed.asMilliseconds();
//		relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y));
//		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height - 1));
//
//		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
//		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
//			relativeNeoCornerPosition.x--;
//			relativeNeoCornerPosition2.x--;
//			if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
//				neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
//				break;
//			}
//		}
//		if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y)).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
//			neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x + 1, relativeNeoCornerPosition.y)).x - sprite_.getGlobalBounds().width;
//		}
//	}
//
//	sf::Vector2i relativePosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height));
//	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x) {
//		neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
//	}
//	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y) {
//		neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
//	}
//
//	relativePosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y));
//	if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x) {
//		neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
//	}
//	if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
//		neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
//	}
//
//	sprite_.setPosition(neoPosition);
//	return;
//}

void DefenseBot::update(sf::Time& elapsed) {
	sf::Vector2f neoPosition = sprite_.getPosition();
	sf::Vector2f positionToReach = neoPosition;

	// The locations of two corners are used to ensure the defense bot can't drive partially into obstacles at weird angles
	sf::Vector2i relativeNeoPosition;
	sf::Vector2i relativeNeoPosition2;

	int drivingSpeedXMultiplier = 0;
	int drivingSpeedYMultiplier = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		drivingSpeedYMultiplier = -1;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		drivingSpeedXMultiplier = -1;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		drivingSpeedYMultiplier = 1;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		drivingSpeedXMultiplier = 1;
	}

	positionToReach.x += elapsed.asMilliseconds() * drivingSpeedXMultiplier * DRIVING_SPEED;
	positionToReach.y += elapsed.asMilliseconds() * drivingSpeedYMultiplier * DRIVING_SPEED;

	neoPosition.x += DRIVING_SPEED * elapsed.asMilliseconds() * drivingSpeedXMultiplier;
	neoPosition.y += DRIVING_SPEED * elapsed.asMilliseconds() * drivingSpeedYMultiplier;
	relativeNeoPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + (sprite_.getGlobalBounds().width * (int)((float)0.5 + (float)0.5 * drivingSpeedXMultiplier)), neoPosition.y + (sprite_.getGlobalBounds().height * (int)((float)0.5 + (float)0.5 * drivingSpeedYMultiplier))));
	relativeNeoPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + (sprite_.getGlobalBounds().width * (int)((float)0.5 + (float)0.5 * drivingSpeedXMultiplier) + (1 - abs(drivingSpeedXMultiplier)) * (sprite_.getGlobalBounds().width - 1)), neoPosition.y + (sprite_.getGlobalBounds().height * (int)((float)0.5 + (float)0.5 * drivingSpeedYMultiplier)) + (1 - abs(drivingSpeedYMultiplier)) * (sprite_.getGlobalBounds().height - 1)));
	
	// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
	while (PlayingField::canThisObjectBeAt(relativeNeoPosition, DEFENSE_TAG) && relativeNeoPosition != PlayingField::findRelativePosition(positionToReach) || PlayingField::canThisObjectBeAt(relativeNeoPosition2, DEFENSE_TAG)) {
		relativeNeoPosition.x += drivingSpeedXMultiplier;
		relativeNeoPosition2.x += drivingSpeedXMultiplier;
		relativeNeoPosition.y += drivingSpeedYMultiplier;
		relativeNeoPosition2.y += drivingSpeedYMultiplier;
		if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoPosition.x) {
			neoPosition.x = PlayingField::findAbsoluteXPosition(OUTSIDE_OF_FIELD_UP_OR_LEFT);
			break;
		} else if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativeNeoPosition.y) {
			neoPosition.y = PlayingField::findAbsoluteYPosition(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT);
			break;
		} else if (PlayingField::findRelativePosition(neoPosition) != relativeNeoPosition) {
			neoPosition.y = PlayingField::findAbsoluteYPosition(relativeNeoPosition.y);
		}
		if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoPosition.y) {
			neoPosition.y = PlayingField::findAbsoluteYPosition(OUTSIDE_OF_FIELD_UP_OR_LEFT);
			break;
		} else if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativeNeoPosition.x) {
			neoPosition.x = PlayingField::findAbsoluteXPosition(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT);
			break;
		} else if (PlayingField::findRelativePosition(neoPosition) != relativeNeoPosition) {
			neoPosition.x = PlayingField::findAbsoluteXPosition(relativeNeoPosition.x);
		}
	}

	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
	//		neoPosition.y -= DRIVING_SPEED * elapsed.asMilliseconds();
	//		relativeNeoCornerPosition = PlayingField::findRelativePosition(neoPosition);
	//		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y));
	//
	//		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
	//		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
	//			relativeNeoCornerPosition.y++;
	//			relativeNeoCornerPosition2.y++;
	//			if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.y) {
	//				neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
	//				break;
	//			}
	//		}
	//		if (PlayingField::findRelativePosition(neoPosition).y != relativeNeoCornerPosition.y && OUTSIDE_OF_FIELD_UP_OR_LEFT != relativeNeoCornerPosition.y) {
	//			neoPosition.y = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).y;
	//		}
	//	}
	
	//	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	//		neoPosition.y += DRIVING_SPEED * elapsed.asMilliseconds();
	//		relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height));
	//		relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y + sprite_.getGlobalBounds().height));
	//
	//		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its y-coordinate accordingly
	//		while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
	//			relativeNeoCornerPosition.y--;
	//			relativeNeoCornerPosition2.y--;
	//			if (relativeNeoCornerPosition.y == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
	//				neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
	//				break;
	//			}
	//		}
	//		if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height)).y != relativeNeoCornerPosition.y && relativeNeoCornerPosition.y != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
	//			neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x, relativeNeoCornerPosition.y + 1)).y - sprite_.getGlobalBounds().height;
	//		}
	//	}
	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	//	neoPosition.x -= DRIVING_SPEED * elapsed.asMilliseconds();
	//	relativeNeoCornerPosition = PlayingField::findRelativePosition(neoPosition);
	//	relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height - 1));

	//	// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
	//	while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
	//		relativeNeoCornerPosition.x++;
	//		relativeNeoCornerPosition2.x++;
	//		if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
	//			neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
	//			break;
	//		}
	//	}
	//	if (PlayingField::findRelativePosition(neoPosition).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
	//		neoPosition.x = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).x;
	//	}
	//} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
	//	neoPosition.x += DRIVING_SPEED * elapsed.asMilliseconds();
	//	relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y));
	//	relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height - 1));

	//	// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
	//	while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
	//		relativeNeoCornerPosition.x--;
	//		relativeNeoCornerPosition2.x--;
	//		if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
	//			neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
	//			break;
	//		}
	//	}
	//	if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y)).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
	//		neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x + 1, relativeNeoCornerPosition.y)).x - sprite_.getGlobalBounds().width;
	//	}
	//}

	//sf::Vector2i relativePosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height));
	//if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x) {
	//	neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
	//}
	//if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y) {
	//	neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
	//}

	//relativePosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y));
	//if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x) {
	//	neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
	//}
	//if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
	//	neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
	//}

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

//void DefenseBot::update(sf::Time& elapsed) {
//	int xDistanceMultiplier = 0;
//	int yDistanceMultiplier = 0;
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//		yDistanceMultiplier = -1;
//	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//		xDistanceMultiplier = -1;
//	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//		yDistanceMultiplier = 1;
//	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//		xDistanceMultiplier = 1;
//	}
//
//	sf::Vector2f neoPosition = sprite_.getPosition();
//
//	// The locations of two corners are used to ensure the defense bot can't drive partially into obstacles at weird angles
//	sf::Vector2i relativeNeoCornerPosition;
//	sf::Vector2i relativeNeoCornerPosition2;
//
//	neoPosition.x += xDistanceMultiplier * DRIVING_SPEED * elapsed.asMilliseconds();
//	neoPosition.y += yDistanceMultiplier * DRIVING_SPEED * elapsed.asMilliseconds();
//	relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + (0.5 + xDistanceMultiplier / 2) * sprite_.getGlobalBounds().width, neoPosition.y + (0.5 + yDistanceMultiplier / 2) * sprite_.getGlobalBounds().height));
//	relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + xDistanceMultiplier * std::abs(sprite_.getGlobalBounds().width - 1), neoPosition.y + yDistanceMultiplier * std::abs(sprite_.getGlobalBounds().height - 1)));
//
//	// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
//	while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
//		relativeNeoCornerPosition.x -= xDistanceMultiplier;
//		relativeNeoCornerPosition2.x -= xDistanceMultiplier;
//		relativeNeoCornerPosition.y -= yDistanceMultiplier;
//		relativeNeoCornerPosition2.y -= yDistanceMultiplier;
//		if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.y || OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativeNeoCornerPosition.y || OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.x || OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativeNeoCornerPosition.x) {
//			if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.y) {
//				neoPosition.y = PlayingField::findAbsoluteYPosition(OUTSIDE_OF_FIELD_UP_OR_LEFT);
//			} else if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativeNeoCornerPosition.y) {
//				neoPosition.y = PlayingField::findAbsoluteYPosition(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT);
//			}
//			if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.x) {
//				neoPosition.x = PlayingField::findAbsoluteXPosition(OUTSIDE_OF_FIELD_UP_OR_LEFT);
//			} else if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativeNeoCornerPosition.x) {
//				neoPosition.x = PlayingField::findAbsoluteXPosition(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT);
//			}
//			break;
//		}
//	}
//	if (PlayingField::findRelativeYPosition(neoPosition.y + (0.5 + yDistanceMultiplier / 2) * sprite_.getGlobalBounds().height) != relativeNeoCornerPosition.y && OUTSIDE_OF_FIELD_UP_OR_LEFT != relativeNeoCornerPosition.y && OUTSIDE_OF_FIELD_DOWN_OR_RIGHT != relativeNeoCornerPosition.y) {
//		neoPosition.y = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).y;
//	}
//	if (PlayingField::findRelativeXPosition(neoPosition.x + (0.5 + xDistanceMultiplier / 2) * sprite_.getGlobalBounds().width) != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_UP_OR_LEFT && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
//		neoPosition.x = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).x;
//	}
//
//	sprite_.setPosition(neoPosition);
//	return;
	//}	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	//	// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its y-coordinate accordingly
	//	if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height)).y != relativeNeoCornerPosition.y && relativeNeoCornerPosition.y != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
	//		neoPosition.y = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x, relativeNeoCornerPosition.y + 1)).y - sprite_.getGlobalBounds().height;
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	//	neoPosition.x -= DRIVING_SPEED * elapsed.asMilliseconds();
	//	relativeNeoCornerPosition = PlayingField::findRelativePosition(neoPosition);
	//	relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height - 1));

	//	// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
	//	while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
	//		relativeNeoCornerPosition.x++;
	//		relativeNeoCornerPosition2.x++;
	//		if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
	//			neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
	//			break;
	//		}
	//	}
	//	if (PlayingField::findRelativePosition(neoPosition).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
	//		neoPosition.x = PlayingField::findAbsolutePosition(relativeNeoCornerPosition).x;
	//	}
	//} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
	//	neoPosition.x += DRIVING_SPEED * elapsed.asMilliseconds();
	//	relativeNeoCornerPosition = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y));
	//	relativeNeoCornerPosition2 = PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height - 1));

	//	// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
	//	while (PlayingField::canThisObjectBeAt(relativeNeoCornerPosition, DEFENSE_TAG) || PlayingField::canThisObjectBeAt(relativeNeoCornerPosition2, DEFENSE_TAG)) {
	//		relativeNeoCornerPosition.x--;
	//		relativeNeoCornerPosition2.x--;
	//		if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
	//			neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
	//			break;
	//		}
	//	}
	//	if (PlayingField::findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y)).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
	//		neoPosition.x = PlayingField::findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x + 1, relativeNeoCornerPosition.y)).x - sprite_.getGlobalBounds().width;
	//	}
	//}
//}