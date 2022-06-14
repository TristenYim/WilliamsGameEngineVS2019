#include "Tower.h"
#include "SelectionBox.h"
#include "Projectile.h"
#define _USE_MATH_DEFINES
#include <math.h>

std::vector<sf::Sprite> Tower::towerSprites;
std::vector<sf::Sprite> Tower::towerRangeSprites;
std::vector<int> Tower::attackDelays;
std::vector<float> Tower::rotationSpeeds;
std::vector<int> Tower::projectilesPerAttacks;
std::vector<int> Tower::betweenProjectilesDelays;
std::vector<int> Tower::towerCosts;
std::vector<std::string> Tower::projectileTextures;
std::vector<float> Tower::projectileSpeeds;
std::vector<int> Tower::projectileDamages;
std::vector<bool> Tower::projectilePiercesEnemies;

Tower::Tower(TowerTypes itype, sf::Vector2f ipos) {
	type_ = itype;

	range_ = towerRangeSprites[itype];
	range_.setPosition(ipos);
	sprite_ = towerSprites[itype];
	sprite_.setPosition(ipos);
	setCollisionCheckEnabled(true);
	assignTag("tower");
}

void Tower::initializeTowerVectors() {
	// This prevents the vectors from breaking since calling this method multiple times would otherwise result in extra data being added to the vectors
	towerSprites.clear();
	towerRangeSprites.clear();
	attackDelays.clear();
	rotationSpeeds.clear();
	projectilesPerAttacks.clear();
	betweenProjectilesDelays.clear();
	towerCosts.clear();

	sf::Sprite towerSpriteToPushBack;
	sf::Sprite rangeToPushBack;
	int range;
	rangeToPushBack.setTexture(GAME.getTexture("Resources/Range Box.png"));
	rangeToPushBack.setColor(sf::Color(254, 254, 254, 100));

	// Cheesy Poofs
	towerSpriteToPushBack.setTexture(GAME.getTexture("Resources/Tower 254.png"));
	towerSpriteToPushBack.setOrigin(sf::Vector2f(towerSpriteToPushBack.getGlobalBounds().width / 2.0, towerSpriteToPushBack.getGlobalBounds().height / 2.0));
	towerSprites.push_back(towerSpriteToPushBack);
	range = 254;
	rangeToPushBack.setScale(sf::Vector2f(range, range));
	rangeToPushBack.setOrigin(rangeToPushBack.getGlobalBounds().width / 2.0 / range, rangeToPushBack.getGlobalBounds().height / 2.0 / range);
	towerRangeSprites.push_back(rangeToPushBack);
	attackDelays.push_back(300);
	rotationSpeeds.push_back(0.4);
	projectilesPerAttacks.push_back(1);
	betweenProjectilesDelays.push_back(0);
	towerCosts.push_back(75);

	projectileTextures.push_back("Resources/Cheesy Poof.png");
	projectileSpeeds.push_back(0.8);
	projectileDamages.push_back(50);
	projectilePiercesEnemies.push_back(false);

	// Sonic Squirrels
	towerSpriteToPushBack.setTexture(GAME.getTexture("Resources/Sonic Squirrels.png"));
	towerSpriteToPushBack.setOrigin(sf::Vector2f(towerSpriteToPushBack.getGlobalBounds().width / 2.0, towerSpriteToPushBack.getGlobalBounds().height / 2.0));
	towerSprites.push_back(towerSpriteToPushBack);
	range = 300;
	rangeToPushBack.setScale(sf::Vector2f(range, range));
	rangeToPushBack.setOrigin(rangeToPushBack.getGlobalBounds().width / 2.0 / range, rangeToPushBack.getGlobalBounds().height / 2.0 / range);
	towerRangeSprites.push_back(rangeToPushBack);
	attackDelays.push_back(750);
	rotationSpeeds.push_back(0.1);
	projectilesPerAttacks.push_back(3);
	betweenProjectilesDelays.push_back(100);
	towerCosts.push_back(500);

	projectileTextures.push_back("Resources/Sonic Blast.png");
	projectileSpeeds.push_back(1.5);
	projectileDamages.push_back(5);
	projectilePiercesEnemies.push_back(true);

	return;
}

int Tower::getCost(TowerTypes type) {
	return towerCosts[type];
}

sf::Sprite Tower::getTowerSprite(TowerTypes type) {
	return towerSprites[type];
}

sf::Sprite Tower::getTowerRangeSprite(TowerTypes type) {
	return towerRangeSprites[type];
}

void Tower::update(sf::Time& elapsed) {
	attackTimer -= elapsed.asMilliseconds();
	if (!objectToTarget.empty()) {
		targetEnemy(elapsed.asMilliseconds());
	}
	objectToTarget.clear();
	return;
}

sf::FloatRect Tower::getCollisionRect() {
	return range_.getGlobalBounds();
}

void Tower::draw() {
	GAME.getRenderWindow().draw(sprite_);
	if (drawRange) {
		GAME.getRenderWindow().draw(range_);
	}
	return;
}

void Tower::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("offense") && objectToTarget.empty()) {
		objectToTarget.push_back(otherGameObject);
	} else if (otherGameObject.hasTag("selection")) {
		SelectionBox& selectionBox_ = dynamic_cast<SelectionBox&>(otherGameObject);
		if (selectionBox_.getCollisionRect().contains(sprite_.getPosition())) {
			drawRange = true;
		} else {
			drawRange = false;
		}
	}
	return;
}

void Tower::targetEnemy(float msElapsed) {
	sf::Vector2f distanceToEnemy = sf::Vector2f(objectToTarget[0].getPosition().x - sprite_.getPosition().x, objectToTarget[0].getPosition().y - sprite_.getPosition().y);

	float rotationToReach = 180 * atan(distanceToEnemy.y / distanceToEnemy.x) / M_PI;
	float currentRotation = sprite_.getRotation();
	if (distanceToEnemy.x > 0) {
		if (0 <= rotationToReach) {
			rotationToReach = 180 + rotationToReach;
		} else {
			rotationToReach = -180 + rotationToReach;
		}
	}
	while (0 > rotationToReach) {
		rotationToReach += 360;
	}

	if ((int)currentRotation != (int)rotationToReach) {
		if ((rotationToReach - currentRotation <= 180.0 && rotationToReach - currentRotation >= 0.0) || rotationToReach - currentRotation < -180) {
			currentRotation += msElapsed * rotationSpeeds[type_];
			if (currentRotation > rotationToReach && rotationToReach - currentRotation > 0) {
				currentRotation = rotationToReach;
			}
		} else {
			currentRotation -= msElapsed * rotationSpeeds[type_];
			if (currentRotation < rotationToReach && rotationToReach - currentRotation < 0) {
				currentRotation = rotationToReach;
			}
		}
		sprite_.setRotation(currentRotation);
	}

	if (((int)(rotationToReach) == (int)currentRotation && 0 >= attackTimer) || (1 < projectilesShot && 0 >= attackTimer)) {
		attackAction(distanceToEnemy);
	}
	return;
}

void Tower::attackAction(sf::Vector2f distanceToEnemy) {
	if (projectilesPerAttacks[type_] > projectilesShot) {
		attackTimer = betweenProjectilesDelays[type_];
		projectilesShot++;
	} else {
		attackTimer = attackDelays[type_];
		projectilesShot = 1;
	}

	ProjectilePtr projectile_;

	switch (type_) {
	case CheesyPoofs: case SonicSquirrels:
		projectile_ = std::make_shared<Projectile>(sprite_.getPosition(), distanceToEnemy, projectileTextures[type_], projectileSpeeds[type_], projectileDamages[type_], projectilePiercesEnemies[type_]);
		break;
	}
	GAME.getCurrentScene().addGameObject(projectile_);
	return;
}