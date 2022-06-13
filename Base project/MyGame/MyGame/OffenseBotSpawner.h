#pragma once
#include "OffenseBot.h";

#include "Engine/GameEngine.h"
const std::string SPAWNING_FILE = "Resources/Spawning Data.txt";

class OffenseBotSpawner : public GameObject {
public:
	OffenseBotSpawner(OffenseType ibotType, float ispawningDelay, float initialDelay, int iamount, bool ispawnBotsOnBottom);

	void update(sf::Time& elapsed);
private:
	OffenseType botType;
	float spawningTimer;
	float spawningDelay;
	int amount;
	bool spawnBotsOnBottom = false;
};

typedef std::shared_ptr<OffenseBotSpawner> OffenseBotSpawnerPtr;