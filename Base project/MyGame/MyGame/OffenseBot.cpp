#include "OffenseBot.h"
#include "PlayingField.h"
#include "Credits.h"
#include "ScoringProjectile.h"
#include "Projectile.h"
#include <fstream>

OffenseBot::OffenseBot(sf::Vector2f ipos, bool spawnOnBottom, OffenseType type) {
	switch (type) {
	case SbaseNshoot:
		sprite_.setTexture(GAME.getTexture("Resources/SbaseNshoot.png"));
		movementSpeed = 0.2;
		hp = 300;
		scoringDelay = 1000;
		percentChanceOfScoring = 50;
		reward = 75;
		break;
	case SbaseGshoot:
		sprite_.setTexture(GAME.getTexture("Resources/SbaseGshoot.png"));
		movementSpeed = 0.2;
		hp = 300;
		scoringDelay = 1000;
		percentChanceOfScoring = 90;
		reward = 100;
		break;
	case SbaseBshoot:
		sprite_.setTexture(GAME.getTexture("Resources/SbaseBshoot.png"));
		movementSpeed = 0.2;
		hp = 300;
		scoringDelay = 2000;
		percentChanceOfScoring = 25;
		reward = 25;
		break;
	case SSbaseGshoot:
		sprite_.setTexture(GAME.getTexture("Resources/SSbaseGshoot.png"));
		movementSpeed = 0.05;
		hp = 2000;
		scoringDelay = 400;
		percentChanceOfScoring = 90;
		reward = 400;
		break;
	case FbaseNshoot:
		sprite_.setTexture(GAME.getTexture("Resources/FbaseNshoot.png"));
		movementSpeed = 0.3;
		hp = 200;
		scoringDelay = 1000;
		percentChanceOfScoring = 50;
		reward = 40;
		break;
	case FbaseGshoot:
		sprite_.setTexture(GAME.getTexture("Resources/FbaseGshoot.png"));
		movementSpeed = 0.3;
		hp = 200;
		scoringDelay = 1000;
		percentChanceOfScoring = 90;
		reward = 60;
		break;
	case FbaseBshoot:
		sprite_.setTexture(GAME.getTexture("Resources/FbaseGshoot.png"));
		movementSpeed = 0.3;
		hp = 200;
		scoringDelay = 2000;
		percentChanceOfScoring = 25;
		reward = 15;
		break;
	case SFbaseNshoot:
		sprite_.setTexture(GAME.getTexture("Resources/SFbaseNshoot.png"));
		movementSpeed = 0.7;
		hp = 50;
		scoringDelay = 500;
		percentChanceOfScoring = 50;
		reward = 25;
		break;
	case SFbaseGshoot:
		sprite_.setTexture(GAME.getTexture("Resources/SFbaseGshoot.png"));
		movementSpeed = 0.7;
		hp = 50;
		scoringDelay = 500;
		percentChanceOfScoring = 90;
		reward = 40;
		break;
	case SFOP:
		sprite_.setTexture(GAME.getTexture("Resources/SFOP.png"));
		movementSpeed = 0.7;
		hp = 400;
		scoringDelay = 300;
		percentChanceOfScoring = 90;
		reward = 400;
		break;
	}

	// The position in modified to spawn the offense bot on the corner of a square. Since this constructor cannot access the playing field, it must take an absolute position input rather than a relative one
	sprite_.setPosition(sf::Vector2f(ipos.x - sprite_.getGlobalBounds().width / 2.0, ipos.y - sprite_.getGlobalBounds().height / 2.0));
	setCollisionCheckEnabled(true);

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
			directions.push_back(GoScore);
			break;
		}
	}
}

void OffenseBot::update(sf::Time& elapsed) {
	if (directions[currentOperation] != GoScore) {
		move(elapsed.asMilliseconds());
	} else {
		scoringTimer -= elapsed.asMilliseconds();
		if (scoringTimer <= 0) {
			scoreAction();
		}
	}
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
		Projectile& projectile_ = dynamic_cast<Projectile&>(otherGameObject);
		hp -= projectile_.getDamage();
		if (0 >= hp) {
			makeDead();
		}
		Credits::addCredit(reward);
	}
	return;
}

sf::Vector2f OffenseBot::getPosition() {
	return sf::Vector2f(sprite_.getPosition().x + sprite_.getGlobalBounds().width, sprite_.getPosition().y + sprite_.getGlobalBounds().height);
}

void OffenseBot::move(float msElapsed) {
	float distance = movementSpeed * msElapsed;
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
}

void OffenseBot::scoreAction() {
	scoringTimer = scoringDelay;
	bool willItHit = true;
	if (1 + rand() % 100 >= percentChanceOfScoring) {
		willItHit = false;
	} 
	ScoringProjectilePtr scoringProjectile_ = std::make_shared<ScoringProjectile>(sf::Vector2f(sprite_.getPosition().x + sprite_.getGlobalBounds().width, sprite_.getPosition().y + sprite_.getGlobalBounds().height / 2.0), willItHit);
	GAME.getCurrentScene().addGameObject(scoringProjectile_);
}