#pragma once

#include "Engine/GameEngine.h"
const std::string SPAWNING_FILE = "Resources/Spawning Data.txt";

class OffenseBotSpawner : public GameObject {
public:
	OffenseBotSpawner(float ispawningDelay, float ibotMovementSpeed);

	void update(sf::Time& elapsed);
private:
	float spawningTimer;
	float spawningDelay;
	float botMovemevntSpeed;
	bool spawnBotsOnBottom = false;
};

typedef std::shared_ptr<OffenseBotSpawner> OffenseBotSpawnerPtr;