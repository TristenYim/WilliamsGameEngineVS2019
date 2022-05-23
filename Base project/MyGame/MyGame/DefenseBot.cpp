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
	sf::Vector2i relativeNeoPosition;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		neoPosition.y -= DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoPosition = playingField_->findRelativePosition(neoPosition);

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoPosition)) {
			relativeNeoPosition.y++;
			if (relativeNeoPosition.y == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT || relativeNeoPosition.y == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				break;
			}
		}
		if (playingField_->findRelativePosition(neoPosition).y != relativeNeoPosition.y) {
			neoPosition.y = playingField_->findAbsolutePosition(relativeNeoPosition).y;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		neoPosition.x -= DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoPosition = playingField_->findRelativePosition(neoPosition);

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoPosition)) {
			relativeNeoPosition.x++;
			if (relativeNeoPosition.x == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT || relativeNeoPosition.x == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				break;
			}
		}
		if (playingField_->findRelativePosition(neoPosition).x != relativeNeoPosition.x) {
			neoPosition.x = playingField_->findAbsolutePosition(relativeNeoPosition).x;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		neoPosition.y += DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoPosition = playingField_->findRelativePosition(neoPosition);

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoPosition)) {
			relativeNeoPosition.y--;
			if (relativeNeoPosition.y == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT || relativeNeoPosition.y == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				break;
			}
		}
		if (playingField_->findRelativePosition(neoPosition).y != relativeNeoPosition.y) {
			neoPosition.y = playingField_->findAbsolutePosition(relativeNeoPosition).y;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		neoPosition.x += DRIVING_SPEED * elapsed.asMilliseconds();
		relativeNeoPosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y));

		// Checks to see if there's an obstacle where the defense bot is trying to go and ajusts its x-coordinate accordingly
		while (playingField_->isAnObstacleAt(relativeNeoPosition)) {
			relativeNeoPosition.x--;
			if (relativeNeoPosition.x == OUTSIDE_OF_FIELD_DOWN_OR_RIGHT || relativeNeoPosition.x == OUTSIDE_OF_FIELD_UP_OR_LEFT) {
				break;
			}
		}
		if (playingField_->findRelativePosition(neoPosition).x != relativeNeoPosition.x) {
			neoPosition.x = playingField_->findAbsolutePosition(relativeNeoPosition).x;
		}
	}

	sf::Vector2i relativePosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height));
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x) {
		neoPosition.x = playingField_->findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_DOWN_OR_RIGHT, 0)).x - sprite_.getGlobalBounds().width;
	}
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y) {
		neoPosition.y = playingField_->findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_DOWN_OR_RIGHT)).y - sprite_.getGlobalBounds().height;
	}

	relativePosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x, neoPosition.y));
	if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x) {
		neoPosition.x = playingField_->findAbsolutePosition(sf::Vector2i(OUTSIDE_OF_FIELD_UP_OR_LEFT, 0)).x;
	}
	if (OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
		neoPosition.y = playingField_->findAbsolutePosition(sf::Vector2i(0, OUTSIDE_OF_FIELD_UP_OR_LEFT)).y;
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