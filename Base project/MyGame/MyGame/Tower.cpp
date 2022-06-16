#include "Tower.h"
#include "SelectionBox.h"
#include "Credits.h"
#include "Projectile.h"
#include "BombProjectile.h"
#include "UpgradeAnimation.h"
#define _USE_MATH_DEFINES
#include <math.h>

std::vector<sf::Sprite> Tower::towerSprites;
std::vector<sf::Sprite> Tower::rangeSprites;
std::vector<int> Tower::attackDelays;
std::vector<float> Tower::rotationSpeeds;
std::vector<int> Tower::projectilesPerAttacks;
std::vector<int> Tower::betweenProjectilesDelays;
std::vector<int> Tower::towerCosts;
std::vector<std::string> Tower::projectileTextures;
std::vector<float> Tower::projectileSpeeds;
std::vector<int> Tower::projectileDamages;
std::vector<bool> Tower::projectilePiercesEnemies;

std::vector<std::vector<float>> Tower::upgradedRanges;
std::vector<std::vector<int>> Tower::upgradedAttackDelayModifiers;
std::vector<std::vector<float>> Tower::upgradedRotationSpeedModifiers;
std::vector<std::vector<int>> Tower::upgradeCosts;
std::vector<std::vector<int>> Tower::upgradedProjectileDamageModifiers;

Tower::Tower(TowerTypes itype, sf::Vector2f ipos) {
	type_ = itype;

	range_ = rangeSprites[itype];
	range_.setPosition(ipos);
	sprite_ = towerSprites[itype];
	sprite_.setPosition(ipos);
	setCollisionCheckEnabled(true);
	assignTag("tower");
}

void Tower::initializeTowerVectors() {
	// This prevents the vectors from breaking since calling this method multiple times would otherwise result in extra data being added to the vectors
	towerSprites.clear();
	rangeSprites.clear();
	attackDelays.clear();
	rotationSpeeds.clear();
	projectilesPerAttacks.clear();
	betweenProjectilesDelays.clear();
	towerCosts.clear();
	projectileTextures.clear();
	projectileSpeeds.clear();
	projectileDamages.clear();
	projectilePiercesEnemies.clear();
	upgradedRanges.clear();
	upgradedAttackDelayModifiers.clear();
	upgradedRotationSpeedModifiers.clear();
	upgradeCosts.clear();
	upgradedProjectileDamageModifiers.clear();

	sf::Sprite towerSpriteToPushBack;
	sf::Sprite rangeToPushBack;
	int range;
	rangeToPushBack.setTexture(GAME.getTexture("Resources/Range Box.png"));
	rangeToPushBack.setColor(sf::Color(254, 254, 254, 100));

	//----------------
	// Cheesy Poofs
	//----------------
	towerSpriteToPushBack.setTexture(GAME.getTexture("Resources/Tower 254.png"));
	towerSpriteToPushBack.setOrigin(sf::Vector2f(towerSpriteToPushBack.getGlobalBounds().width / 2.0, towerSpriteToPushBack.getGlobalBounds().height / 2.0));
	towerSprites.push_back(towerSpriteToPushBack);
	range = 254;
	rangeToPushBack.setScale(sf::Vector2f(range, range));
	rangeToPushBack.setOrigin(rangeToPushBack.getGlobalBounds().width / 2.0 / range, rangeToPushBack.getGlobalBounds().height / 2.0 / range);
	rangeSprites.push_back(rangeToPushBack);

	attackDelays.push_back(300);
	rotationSpeeds.push_back(0.4);
	projectilesPerAttacks.push_back(1);
	betweenProjectilesDelays.push_back(0);
	towerCosts.push_back(75);

	upgradedRanges.push_back(std::vector<float>{ 0, 280, 320, 380, 450 });
	upgradedAttackDelayModifiers.push_back(std::vector<int>{ 0, 25, 60, 100, 150});
	upgradedRotationSpeedModifiers.push_back(std::vector<float>{ 0, 0.05, 0.1, 0.2, 0.4 });
	upgradeCosts.push_back(std::vector<int>{ 50, 75, 120, 254, 0 });
	upgradedProjectileDamageModifiers.push_back(std::vector<int>{ 0, 10, 25, 40, 75 });

	projectileTextures.push_back("Resources/Cheesy Poof.png");
	projectileSpeeds.push_back(1.5);
	projectileDamages.push_back(50);
	projectilePiercesEnemies.push_back(false);

	//-------------------
	// Sonic Squirrels
	//-------------------
	towerSpriteToPushBack.setTexture(GAME.getTexture("Resources/Sonic Squirrels.png"));
	towerSpriteToPushBack.setOrigin(sf::Vector2f(towerSpriteToPushBack.getGlobalBounds().width / 2.0, towerSpriteToPushBack.getGlobalBounds().height / 2.0));
	towerSprites.push_back(towerSpriteToPushBack);
	range = 200;
	rangeToPushBack.setScale(sf::Vector2f(range, range));
	rangeToPushBack.setOrigin(rangeToPushBack.getGlobalBounds().width / 2.0 / range, rangeToPushBack.getGlobalBounds().height / 2.0 / range);
	rangeSprites.push_back(rangeToPushBack);

	attackDelays.push_back(750);
	rotationSpeeds.push_back(0.1);
	projectilesPerAttacks.push_back(3);
	betweenProjectilesDelays.push_back(100);
	towerCosts.push_back(500);

	upgradedRanges.push_back(std::vector<float>{ 0, 230, 265, 300, 360 });
	upgradedAttackDelayModifiers.push_back(std::vector<int>{ 0, 100, 150, 250, 450});
	upgradedRotationSpeedModifiers.push_back(std::vector<float>{ 0, 0.05, 0.05, 0.1, 0.2 });
	upgradeCosts.push_back(std::vector<int>{ 200, 140, 285, 400, 0 });
	upgradedProjectileDamageModifiers.push_back(std::vector<int>{ 0, 0, 1, 3, 5 });

	projectileTextures.push_back("Resources/Sonic Blast.png");
	projectileSpeeds.push_back(1.8);
	projectileDamages.push_back(5);
	projectilePiercesEnemies.push_back(true);

	//--------------
	// Bomb Squad
	//--------------
	towerSpriteToPushBack.setTexture(GAME.getTexture("Resources/Bomb Squad.png"));
	towerSpriteToPushBack.setOrigin(sf::Vector2f(towerSpriteToPushBack.getGlobalBounds().width / 2.0, towerSpriteToPushBack.getGlobalBounds().height / 2.0));
	towerSprites.push_back(towerSpriteToPushBack);
	range = 500;
	rangeToPushBack.setScale(sf::Vector2f(range, range));
	rangeToPushBack.setOrigin(rangeToPushBack.getGlobalBounds().width / 2.0 / range, rangeToPushBack.getGlobalBounds().height / 2.0 / range);
	rangeSprites.push_back(rangeToPushBack);

	attackDelays.push_back(1600);
	rotationSpeeds.push_back(0.1);
	projectilesPerAttacks.push_back(1);
	betweenProjectilesDelays.push_back(0);
	towerCosts.push_back(120);

	upgradedRanges.push_back(std::vector<float>{ 0, 550, 615, 700, 800 });
	upgradedAttackDelayModifiers.push_back(std::vector<int>{ 0, 100, 225, 400, 600 });
	upgradedRotationSpeedModifiers.push_back(std::vector<float>{ 0, 0.03, 0.04, 0.06, 0.1 });
	upgradeCosts.push_back(std::vector<int>{ 90, 120, 180, 240, 0 });
	upgradedProjectileDamageModifiers.push_back(std::vector<int>{ 10, 25, 50, 80, 120 });

	projectileTextures.push_back("Resources/Bomb.png");
	projectileSpeeds.push_back(0.7);
	projectileDamages.push_back(80);
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
	return rangeSprites[type];
}

int Tower::getUpgradeCost() {
	return upgradeCosts[type_][level];
}

void Tower::update(sf::Time& elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		pressedU = true;
	} else {
		pressedU = false;
	}
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

sf::FloatRect Tower::getTowerSpriteCollisionRect() {
	return sprite_.getGlobalBounds();
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
		SelectionBox::setUpgradeCostToDisplay(upgradeCosts[type_][level]);
		if (upgradeCosts[type_][level] <= Credits::getCredit() && sf::Keyboard::isKeyPressed(sf::Keyboard::U) && !pressedU) {
			upgrade();
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
			currentRotation += msElapsed * (rotationSpeeds[type_] + upgradedRotationSpeedModifiers[type_][level]);
			if (currentRotation > rotationToReach && rotationToReach - currentRotation > 0) {
				currentRotation = rotationToReach;
			}
		} else {
			currentRotation -= msElapsed * (rotationSpeeds[type_] + upgradedRotationSpeedModifiers[type_][level]);
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
		attackTimer = attackDelays[type_] - upgradedAttackDelayModifiers[type_][level];
		projectilesShot = 1;
	}

	fireSound_.setBuffer(GAME.getSoundBuffer("Resources/Space-Cannon.wav"));
	fireSound_.play();

	ProjectilePtr projectile_;

	switch (type_) {
	case CheesyPoofs: case SonicSquirrels:
		projectile_ = std::make_shared<Projectile>(sprite_.getPosition(), projectileTextures[type_], distanceToEnemy, projectileSpeeds[type_], projectileDamages[type_] + upgradedProjectileDamageModifiers[type_][level], projectilePiercesEnemies[type_]);
		break;
	case BombSquad:
		BombProjectilePtr bombProjectile_ = std::make_shared<BombProjectile>(sprite_.getPosition(), projectileTextures[type_], distanceToEnemy, projectileSpeeds[type_], projectileDamages[type_] + upgradedProjectileDamageModifiers[type_][level], projectilePiercesEnemies[type_], level);
		GAME.getCurrentScene().addGameObject(bombProjectile_);
		return;
	}
	GAME.getCurrentScene().addGameObject(projectile_);
	return;
}

void Tower::upgrade() {
	if (4 > level) {
		UpgradeAnimationPtr upgradeAnimation_ = std::make_shared<UpgradeAnimation>(sprite_.getPosition());
		GAME.getCurrentScene().addGameObject(upgradeAnimation_);
		Credits::addCredit(-upgradeCosts[type_][level]);
		level++;
		range_.setScale(sf::Vector2f(upgradedRanges[type_][level], upgradedRanges[type_][level]));
	}
	return;
}