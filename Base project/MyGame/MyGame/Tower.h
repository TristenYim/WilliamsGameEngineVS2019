#pragma once

#include "Engine/GameEngine.h"
#include "OffenseBot.h"
#include "Projectile.h"

enum TowerTypes { CheesyPoofs, SonicSquirrels };

class Tower : public GameObject {
public:
	Tower(TowerTypes itype, sf::Vector2f ipos);

	static void initializeTowerVectors();
	static int getCost(TowerTypes type);
	static sf::Sprite getTowerSprite(TowerTypes type);
	static sf::Sprite getTowerRangeSprite(TowerTypes type);

	int getUpgradeCost();

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	sf::FloatRect getTowerSpriteCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
private:
	static std::vector<sf::Sprite> towerSprites;
	static std::vector<sf::Sprite> rangeSprites;
	static std::vector<int> attackDelays;
	static std::vector<float> rotationSpeeds;
	static std::vector<int> projectilesPerAttacks;
	static std::vector<int> betweenProjectilesDelays;
	static std::vector<int> towerCosts;

	static std::vector<std::string> projectileTextures;
	static std::vector<float> projectileSpeeds;
	static std::vector<int> projectileDamages;
	static std::vector<bool> projectilePiercesEnemies;

	static std::vector<std::vector<float>> upgradedRanges;
	static std::vector<std::vector<int>> upgradedAttackDelayModifiers;
	static std::vector<std::vector<float>> upgradedRotationSpeedModifiers;
	static std::vector<std::vector<int>> upgradeCosts;
	static std::vector<std::vector<int>> upgradedProjectileDamageModifiers;

	bool pressedU = false;

	TowerTypes type_;
	sf::Sprite range_;
	std::vector<GameObject> objectToTarget;
	bool drawRange = false;
	float attackTimer = 0.0;
	int projectilesShot = 1;
	int level = 0;

	void targetEnemy(float msElapsed);
	void attackAction(sf::Vector2f distanceToEnemy);
	void upgrade();
};

typedef std::shared_ptr<Tower> TowerPtr;