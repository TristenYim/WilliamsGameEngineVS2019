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

	sf::Vector2f movementVector(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movementVector.y -= DRIVING_SPEED * elapsed.asMilliseconds();
		justPressedW = true;
	} else {
		justPressedW = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movementVector.x -= DRIVING_SPEED * elapsed.asMilliseconds();
		justPressedA = true;
	} else {
		justPressedA = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movementVector.y += DRIVING_SPEED * elapsed.asMilliseconds();
		justPressedS = true;
	} else {
		justPressedS = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movementVector.x += DRIVING_SPEED * elapsed.asMilliseconds();
		justPressedD = true;
	} else {
		justPressedD = false;
	}
	sf::Vector2f neoPosition;
	neoPosition.x = sprite_.getPosition().x + movementVector.x;
	neoPosition.y = sprite_.getPosition().y + movementVector.y;

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

void DefenseBot::handleCollision(GameObject& otherObject_) {
	if (otherObject_.hasTag("obstacle")) {
		if (justPressedW) {
			sprite_.setPosition(sf::Vector2f(sprite_.getPosition().x, otherObject_.getPosition().y - otherObject_.getCollisionRect().height));
		}
		if (justPressedA) {
			sprite_.setPosition(sf::Vector2f(sprite_.getPosition().x, otherObject_.getPosition().y - otherObject_.getCollisionRect().height));
		}
	}
}