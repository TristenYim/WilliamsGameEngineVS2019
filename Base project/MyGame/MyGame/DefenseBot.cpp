#include "DefenseBot.h"
#include "GameScene.h"
#include "PlayingField.h"
#include "Obstacle.h"

DefenseBot::DefenseBot(sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Orange Square.png"));
	sprite_.setPosition(ipos);
	assignTag("pc");
}

void DefenseBot::update(sf::Time& elapsed) {
	GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();
	PlayingFieldPtr playingField_ = (PlayingFieldPtr&)currentScene_.getGameObject("field");

	sf::Vector2f neoPosition = sprite_.getPosition();

	// The locations of two corners are used to ensure the defense bot can't drive partially into obstacles at weird angles
	sf::Vector2i relativeNeoCornerPosition;
	sf::Vector2i relativeNeoCornerPosition2;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		neoPosition.y -= DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = playingField_->findRelativePosition(neoPosition);
		relativeNeoCornerPosition2 = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoCornerPosition) || playingField_->isAnObstacleAt(relativeNeoCornerPosition2)) {
			relativeNeoCornerPosition.y++;
			relativeNeoCornerPosition2.y++;
			if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativeNeoCornerPosition.y) {
				neoPosition.y = playingField_->findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
				break;
			}
		}
		if (playingField_->findRelativePosition(neoPosition).y != relativeNeoCornerPosition.y && OUTSIDE_OF_FIELD_UP_OR_LEFT != relativeNeoCornerPosition.y) {
			neoPosition.y = playingField_->findAbsolutePosition(relativeNeoCornerPosition).y;
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		neoPosition.y += DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height));
		relativeNeoCornerPosition2 = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - 1, neoPosition.y + sprite_.getGlobalBounds().height));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its y-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoCornerPosition) || playingField_->isAnObstacleAt(relativeNeoCornerPosition2)) {
			relativeNeoCornerPosition.y--;
			relativeNeoCornerPosition2.y--;
			if (relativeNeoCornerPosition.y == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				neoPosition.y = playingField_->findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
				break;
			}
		}
		if (playingField_->findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height)).y != relativeNeoCornerPosition.y && relativeNeoCornerPosition.y != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
			neoPosition.y = playingField_->findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x, relativeNeoCornerPosition.y + 1)).y - sprite_.getGlobalBounds().height;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		neoPosition.x -= DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = playingField_->findRelativePosition(neoPosition);
		relativeNeoCornerPosition2 = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height - 1));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoCornerPosition) || playingField_->isAnObstacleAt(relativeNeoCornerPosition2)) {
			relativeNeoCornerPosition.x++;
			relativeNeoCornerPosition2.x++;
			if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
				neoPosition.x = playingField_->findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
				break;
			}
		}
		if (playingField_->findRelativePosition(neoPosition).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_DOWN_OR_RIGHT) {
			neoPosition.x = playingField_->findAbsolutePosition(relativeNeoCornerPosition).x;
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		neoPosition.x += DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoCornerPosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y));
		relativeNeoCornerPosition2 = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height - 1));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoCornerPosition) || playingField_->isAnObstacleAt(relativeNeoCornerPosition2)) {
			relativeNeoCornerPosition.x--;
			relativeNeoCornerPosition2.x--;
			if (relativeNeoCornerPosition.x == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				neoPosition.x = playingField_->findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
				break;
			}
		}
		if (playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y)).x != relativeNeoCornerPosition.x && relativeNeoCornerPosition.x != OUTSIDE_OF_FIELD_UP_OR_LEFT) {
			neoPosition.x = playingField_->findAbsolutePosition(sf::Vector2i(relativeNeoCornerPosition.x + 1, relativeNeoCornerPosition.y)).x - sprite_.getGlobalBounds().width;
		}
	}

	//sf::Vector2i relativePosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height));
	//if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x) {
	//	neoPosition.x = playingField_->findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
	//}
	//if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y) {
	//	neoPosition.y = playingField_->findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
	//}

	//relativePosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y));
	//if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x) {
	//	neoPosition.x = playingField_->findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
	//}
	//if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
	//	neoPosition.y = playingField_->findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
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