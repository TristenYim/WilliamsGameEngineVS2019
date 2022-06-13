#pragma once

#include "Engine/GameEngine.h"
#include "OffenseBotSpawner.h"

const std::string WAVE_FILE = "Waves.txt";

class Wave : public GameObject {
public:
	Wave(int iwaveNumber);

	void update(sf::Time& elapsed);
private:
	int waveNumber;
	int reward;
	float checkForEndOfWaveTimer = 0;
	bool startedWave = false;
	std::vector<OffenseBotSpawnerPtr> botSpawners;
	std::string getstring(std::string sinput, char delimiter, int delimiter_skip);
};

typedef std::shared_ptr<Wave> WavePtr;