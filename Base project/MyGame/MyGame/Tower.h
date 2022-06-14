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

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
private:
	static std::vector<sf::Sprite> towerSprites;
	static std::vector<sf::Sprite> towerRangeSprites;
	static std::vector<int> attackDelays;
	static std::vector<float> rotationSpeeds;
	static std::vector<int> projectilesPerAttacks;
	static std::vector<int> betweenProjectilesDelays;
	static std::vector<int> towerCosts;
	static std::vector<std::string> projectileTextures;
	static std::vector<float> projectileSpeeds;
	static std::vector<int> projectileDamages;
	static std::vector<bool> projectilePiercesEnemies;

	sf::Sprite range_;
	bool drawRange = false;
	float attackTimer = 0.0;
	std::vector<GameObject> objectToTarget;
	int level = 1;

	TowerTypes type_;
	int projectilesShot = 1;

	void attackAction(sf::Vector2f distanceToEnemy);
	void targetEnemy(float msElapsed);
	//virtual void levelUp();
};

typedef std::shared_ptr<Tower> TowerPtr;