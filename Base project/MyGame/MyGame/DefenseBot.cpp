#include "DefenseBot.h"
#include "PlayingField.h"
#include "Score.h"
#include "BlockingTimerText.h"

DefenseBot::DefenseBot(sf::Vector2f ipos) {
	sprite_.setTexture(GAME.getTexture("Resources/Defense Bot.png"));
	sprite_.setPosition(ipos);

	blockingDelay = 3000;
	blockingCooldown = -5000;
	blockingPenaltyCooldown = 2000;
	blockingTimer = blockingDelay;

	assignTag(DEFENSE_TAG);
}

void DefenseBot::update(sf::Time& elapsed) {
	sf::Vector2f neoPosition = sprite_.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveInADirection(neoPosition, Up, elapsed.asMilliseconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveInADirection(neoPosition, Left, elapsed.asMilliseconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveInADirection(neoPosition, Down, elapsed.asMilliseconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveInADirection(neoPosition, Right, elapsed.asMilliseconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && blockingTimer >= 0) {
		blockingTimer -= elapsed.asMilliseconds();
		BlockingTimerText::setVisibility(true);
		BlockingTimerText::setColor(sf::Color(200, 150, 100));
		BlockingTimerText::setSecondsInTimer(int(blockingTimer / 1000) + 1);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && 0 >= blockingTimer) {
		blockingTimer = blockingPenaltyCooldown;
		Scores::majorPenalty();
	} else if (blockingDelay > blockingTimer && 0 < blockingTimer) {
		blockingTimer = blockingCooldown;
	} else if (0 >= blockingTimer) {
		blockingTimer += elapsed.asMilliseconds();
		if (blockingTimer >= 0) {
			blockingTimer = blockingDelay;
		}
		BlockingTimerText::setVisibility(true);
		BlockingTimerText::setColor(sf::Color(0, 254, 200));
		BlockingTimerText::setSecondsInTimer(abs(int(blockingTimer / 1000)) + 1);
	} else {
		BlockingTimerText::setVisibility(false);
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

void DefenseBot::handleCollision(GameObject& otherGameObject) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && otherGameObject.hasTag("scoringprojectile")) {
		otherGameObject.makeDead();
	}
	return;
}

void DefenseBot::moveInADirection(sf::Vector2f& neoPosition, direction direction_, int msElapsed) {
	sf::Vector2f positionToReach = neoPosition;
	sf::Vector2f positionToCheck = neoPosition;
	sf::Vector2f positionToCheck2 = sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y + sprite_.getGlobalBounds().height);
	sf::Vector2f positionToCheck3 = sf::Vector2f(neoPosition.x + sprite_.getGlobalBounds().width, neoPosition.y);
	sf::Vector2f positionToCheck4 = sf::Vector2f(neoPosition.x, neoPosition.y + sprite_.getGlobalBounds().height);

	int xMovementIncrement = 0;
	int xCheckIncrement = 0;
	int yMovementIncrement = 0;
	int yCheckIncrement = 0;

	if (Up == direction_) {
		yMovementIncrement = -1;
	} else if (Left == direction_) {
		xMovementIncrement = -1;
	} else if (Right == direction_) {
		xMovementIncrement = 1;
	} else if (Down == direction_) {
		yMovementIncrement = 1;
	}

	positionToReach.x += (int)(xMovementIncrement * DRIVING_SPEED * msElapsed);
	positionToReach.y += (int)(yMovementIncrement * DRIVING_SPEED * msElapsed);

	while (true) {
		positionToCheck.x += xMovementIncrement;
		positionToCheck.y += yMovementIncrement;
		positionToCheck2.x += xMovementIncrement;
		positionToCheck2.y += yMovementIncrement;
		positionToCheck3.x += xMovementIncrement;
		positionToCheck3.y += yMovementIncrement;
		positionToCheck4.x += xMovementIncrement;
		positionToCheck4.y += yMovementIncrement;
		if (positionToCheck == positionToReach) {
			neoPosition = positionToReach;
			return;
		} else if (!PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(positionToCheck), DEFENSE_TAG)) {
			neoPosition = sf::Vector2f(positionToCheck.x - xMovementIncrement, positionToCheck.y - yMovementIncrement);
			return;
		} else if (!PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(positionToCheck2), DEFENSE_TAG)) {
			neoPosition = sf::Vector2f(positionToCheck2.x - xMovementIncrement - sprite_.getGlobalBounds().width, positionToCheck2.y - yMovementIncrement - sprite_.getGlobalBounds().height);
			return;
		} else if (!PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(positionToCheck3), DEFENSE_TAG)) {
			neoPosition = sf::Vector2f(positionToCheck2.x - xMovementIncrement - sprite_.getGlobalBounds().width, positionToCheck2.y - yMovementIncrement);
			return;
		} else if (!PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(positionToCheck4), DEFENSE_TAG)) {
			neoPosition = sf::Vector2f(positionToCheck2.x - xMovementIncrement, positionToCheck2.y - yMovementIncrement - sprite_.getGlobalBounds().height);
			return;
		}
	}
}