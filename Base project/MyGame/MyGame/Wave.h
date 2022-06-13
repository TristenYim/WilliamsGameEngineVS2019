#pragma once

#include "Engine/GameEngine.h"
#include "OffenseBotSpawner.h"

const std::string WAVE_FILE = "Waves.txt";

class Wave : public TextObject {
public:
	Wave(int iwaveNumber, sf::Vector2f pos, int charSize, sf::Color textColor);

	static void initializeTotalWaves();

	void update(sf::Time& elapsed);
private:
	int waveNumber;
	static int totalWaves;
	int reward;
	float checkForEndOfWaveTimer = 0;
	bool startedWave = false;
	std::vector<OffenseBotSpawnerPtr> botSpawners;
	std::string getstring(std::string sinput, char delimiter, int delimiter_skip);
};

typedef std::shared_ptr<Wave> WavePtr;