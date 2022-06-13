#include "Wave.h"
#include "GameScene.h"
#include "Credits.h"
#include "fstream"

Wave::Wave(int iwaveNumber) {
	std::ifstream waveFile;
	waveFile.open(WAVE_FILE);
	std::string waveFileLine;
	waveNumber = iwaveNumber;
	for (int row = 0; getline(waveFile, waveFileLine) && row < waveNumber; row++) {
	}
	int delimitersSkipped = 0;
	int totalDelimiters = 0;
	for (int index = 0; waveFileLine.size() > index; index++) {
		if (',' == waveFileLine[index]) {
			totalDelimiters++;
		}
	}
	float ispawningDelay;
	float iinitialDelay;
	int iamount;
	while (totalDelimiters > delimitersSkipped) {
		std::string botTypeString = getstring(waveFileLine, ',', delimitersSkipped);
		delimitersSkipped++;
		ispawningDelay = stof(getstring(waveFileLine, ',', delimitersSkipped));
		delimitersSkipped++;
		iinitialDelay = stof(getstring(waveFileLine, ',', delimitersSkipped));
		delimitersSkipped++;
		iamount = stoi(getstring(waveFileLine, ',', delimitersSkipped));
		delimitersSkipped++;
		bool ispawnBotsOnBottom = stoi(getstring(waveFileLine, ',', delimitersSkipped));
		delimitersSkipped++;
		OffenseType ibotType;
		if ("SbaseNshoot" == botTypeString) {
			ibotType = SbaseNshoot;
		} else if ("SbaseGshoot" == botTypeString) {
			ibotType = SbaseGshoot;
		} else if ("SbaseBshoot" == botTypeString) {
			ibotType = SbaseBshoot;
		} else if ("SSbaseGshoot" == botTypeString) {
			ibotType = SSbaseGshoot;
		} else if ("FbaseNshoot" == botTypeString) {
			ibotType = FbaseNshoot;
		} else if ("FbaseGshoot" == botTypeString) {
			ibotType = FbaseGshoot;
		} else if ("FbaseNshoot" == botTypeString) {
			ibotType = FbaseBshoot;
		} else if ("SFbaseNshoot" == botTypeString) {
			ibotType = SFbaseNshoot;
		} else if ("SFbaseGshoot" == botTypeString) {
			ibotType = SFbaseGshoot;
		} else if ("SFOP" == botTypeString) {
			ibotType = SFOP;
		}
		OffenseBotSpawnerPtr botSpawner = std::make_shared<OffenseBotSpawner>(ibotType, ispawningDelay, iinitialDelay, iamount, ispawnBotsOnBottom);
		botSpawners.push_back(botSpawner);
	}
	reward = 500 + waveNumber * 25;
	checkForEndOfWaveTimer = iinitialDelay + ispawningDelay * iamount;
	assignTag("wave");
}

void Wave::update(sf::Time& elapsed) {
	if (!startedWave && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		startedWave = true;
		for (int index = 0; botSpawners.size() > index; index++) {
			GAME.getCurrentScene().addGameObject(botSpawners[index]);
		}
	} else if (startedWave && checkForEndOfWaveTimer > 0) {
		checkForEndOfWaveTimer -= elapsed.asMilliseconds();
	} else if (0 >= checkForEndOfWaveTimer) {
		GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();
		if (!currentScene_.doesAnObjectWithThisTagExist(OFFENSE_TAG)) {
			Credits::addCredit(reward);
			WavePtr nextWave_ = std::make_shared<Wave>(waveNumber + 1);
			currentScene_.addGameObject(nextWave_);
			makeDead();
		}
	}
	return;
}

std::string Wave::getstring(std::string sinput, char delimiter, int delimiter_skip) {
	std::string soutput;
	int index = 0;
	for (int delimiters = 0; delimiters < delimiter_skip && sinput.size() > index; index++) {
		if (delimiter == sinput[index]) {
			delimiters++;
		}
	}
	while (sinput[index] != delimiter && sinput.size() > index) {
		soutput += sinput[index];
		index++;
	}
	return soutput;
}