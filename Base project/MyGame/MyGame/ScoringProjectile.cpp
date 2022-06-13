#include "ScoringProjectile.h"
#include "Score.h"
#include "PlayingField.h"

ScoringProjectile::ScoringProjectile(sf::Vector2f ipos, bool willItHit) {
	sprite_.setTexture(GAME.getTexture("Resources/Steamworks.png"));
	sprite_.setPosition(ipos);
	sprite_.setOrigin(sprite_.getGlobalBounds().width / 2.0, sprite_.getGlobalBounds().height / 2.0);
	setCollisionCheckEnabled(true);

	sf::Vector2f distanceFromTarget = sf::Vector2f(Scores::getPosition().x - ipos.x, Scores::getPosition().y - ipos.y);
	if (!willItHit) {
		float distanceFromTop = PlayingField::getTopLeftCornerPos().y - ipos.y;
		float distanceFromBottom = PlayingField::getBottomRightCornerPos().y - ipos.y;
		float generatedYPosition;
		float yDistanceToGoal = distanceFromTarget.y;

		// The loop below generates a target that misses that is center-weighted by generating 3 targets and picking the one closest to the goal. I do it this way because it was the simplest and easiest one to come up with.
		for (int reps = 0; reps < 3; reps++) {
			generatedYPosition = distanceFromTop + (float)rand() / (float)RAND_MAX * (distanceFromBottom - distanceFromTop);
			if (generatedYPosition <= Scores::getPosition().y - ipos.y + 32 && generatedYPosition >= Scores::getPosition().y - ipos.y - 32) {
				if (generatedYPosition <= Scores::getPosition().y && generatedYPosition >= 0) {
					generatedYPosition = Scores::getPosition().y - ipos.y - 32;
				} else {
					generatedYPosition = Scores::getPosition().y - ipos.y + 32;
				}
			}
			if (0 == reps) {
				distanceFromTarget.y = generatedYPosition;
			} else if (abs(yDistanceToGoal - distanceFromTarget.y) >= abs(yDistanceToGoal - generatedYPosition)) {
				distanceFromTarget.y = generatedYPosition;
			}
		}
	}

	float speedAdjustmentMultiplier = 0.1 / sqrt(distanceFromTarget.x * distanceFromTarget.x + distanceFromTarget.y + distanceFromTarget.y);
	movementVector = sf::Vector2f(distanceFromTarget.x * speedAdjustmentMultiplier, distanceFromTarget.y * speedAdjustmentMultiplier);

	assignTag("ScoringProjectile");
}

void ScoringProjectile::update(sf::Time& elapsed) {
	sprite_.move(movementVector.x * elapsed.asMilliseconds(), movementVector.y * elapsed.asMilliseconds());
	sf::Vector2i relativePosition = PlayingField::findRelativePosition(sprite_.getPosition());
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.x || OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == relativePosition.y || OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.x || OUTSIDE_OF_FIELD_UP_OR_LEFT == relativePosition.y) {
		makeDead();
	}
	return;
}

void ScoringProjectile::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect ScoringProjectile::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void ScoringProjectile::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("scoreobject")) {
		Scores::addEnemyScore(1);
		makeDead();
	}
	return;
}