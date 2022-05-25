#include "OffenseBot.h"
#include "GameScene.h"
#include "PlayingField.h"

OffenseBot::OffenseBot(sf::Vector2f ipos, float imovementSpeed) {
	sprite_.setTexture(GAME.getTexture("Resources/Blue Square.png"));

	// The position in modified to spawn the offense bot on the corner of a square. Since this constructor cannot access the playing field, it must take an absolute position input rather than a relative one
	sprite_.setPosition(sf::Vector2f(ipos.x - sprite_.getGlobalBounds().width / 2.0, ipos.y - sprite_.getGlobalBounds().height / 2.0));
	movementSpeed = imovementSpeed;
	assignTag(OFFENSE_TAG);
}

void OffenseBot::update(sf::Time& elapsed) {
	GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();
	PlayingFieldPtr playingField_ = (PlayingFieldPtr&)currentScene_.getGameObject("field");

	float distance = movementSpeed * elapsed.asMilliseconds();
	sf::Vector2f neoPosition = sprite_.getPosition();
	sf::Vector2i relativeNeoPosition = playingField_->findRelativePosition(sprite_.getPosition());

	if (distance > 0) {
		if (directions[currentOperation] == GoUp) {
			relativeNeoPosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height - distance));
			if (playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x, relativeNeoPosition.y - 2), OFFENSE_TAG)) {
				neoPosition.y -= distance;
				distance = 0;
			} else {
				while (!playingField_->canThisObjectBeAt(relativeNeoPosition, OFFENSE_TAG)) {
					relativeNeoPosition.y++;
				}

				neoPosition = sf::Vector2f(playingField_->findAbsolutePosition(relativeNeoPosition).x - sprite_.getGlobalBounds().width / 2.0, playingField_->findAbsolutePosition(relativeNeoPosition).y - sprite_.getGlobalBounds().height / 2.0);
				distance -= sprite_.getPosition().y - neoPosition.y;

				if (!playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x, relativeNeoPosition.y - 2), OFFENSE_TAG)) {
					currentOperation++;
				}
			}
		}
		if (directions[currentOperation] == GoRight) {
			relativeNeoPosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width + distance, neoPosition.y + sprite_.getGlobalBounds().height));
			if (playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x + 1, relativeNeoPosition.y), OFFENSE_TAG)) {
				neoPosition.x += distance;
				distance = 0;
			} else {
				while (!playingField_->canThisObjectBeAt(relativeNeoPosition, OFFENSE_TAG)) {
					relativeNeoPosition.x--;
				}

				neoPosition = sf::Vector2f(playingField_->findAbsolutePosition(relativeNeoPosition).x - sprite_.getGlobalBounds().width / 2.0, playingField_->findAbsolutePosition(relativeNeoPosition).y - sprite_.getGlobalBounds().height / 2.0);
				distance -= neoPosition.x - sprite_.getPosition().x;

				if (!playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x + 1, relativeNeoPosition.y), OFFENSE_TAG)) {
					currentOperation++;
				}
			}
		}
		if (directions[currentOperation] == GoDown) {
			relativeNeoPosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height + distance));
			if (playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x, relativeNeoPosition.y + 1), OFFENSE_TAG)) {
				neoPosition.y += distance;
				distance = 0;
			} else {
				while (!playingField_->canThisObjectBeAt(relativeNeoPosition, OFFENSE_TAG)) {
					relativeNeoPosition.y--;
				}

				neoPosition = sf::Vector2f(playingField_->findAbsolutePosition(relativeNeoPosition).x - sprite_.getGlobalBounds().width / 2.0, playingField_->findAbsolutePosition(relativeNeoPosition).y - sprite_.getGlobalBounds().height / 2.0);
				distance -= neoPosition.y - sprite_.getPosition().y;

				if (!playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x, relativeNeoPosition.y + 1), OFFENSE_TAG)) {
					currentOperation++;
				}
			}
		}
		if (directions[currentOperation] == GoLeft) {
			relativeNeoPosition = playingField_->findRelativePosition(sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width - distance, neoPosition.y + sprite_.getGlobalBounds().height));
			if (playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x - 2, relativeNeoPosition.y), OFFENSE_TAG)) {
				neoPosition.x -= distance;
				distance = 0;
			} else {
				while (!playingField_->canThisObjectBeAt(relativeNeoPosition, OFFENSE_TAG)) {
					relativeNeoPosition.x++;
				}

				neoPosition = sf::Vector2f(playingField_->findAbsolutePosition(relativeNeoPosition).x - sprite_.getGlobalBounds().width / 2.0, playingField_->findAbsolutePosition(relativeNeoPosition).y - sprite_.getGlobalBounds().height / 2.0);
				distance -= sprite_.getPosition().x - neoPosition.x;

				if (!playingField_->canThisObjectBeAt(sf::Vector2i(relativeNeoPosition.x - 2, relativeNeoPosition.y), OFFENSE_TAG)) {
					currentOperation++;
				}
			}
		}
	}
	sprite_.setPosition(neoPosition);
}

void OffenseBot::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}