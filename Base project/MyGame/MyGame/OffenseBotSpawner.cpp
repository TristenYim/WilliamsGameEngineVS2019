#include "OffenseBotSpawner.h"
#include "PlayingField.h"

OffenseBotSpawner::OffenseBotSpawner(OffenseType ibotType, float ispawningDelay, float initialDelay, int iamount, bool ispawnBotsOnBottom) {
	botType = ibotType;
	spawningDelay = ispawningDelay;
	spawningTimer = ispawningDelay + initialDelay;
	amount = iamount;
	spawnBotsOnBottom = ispawnBotsOnBottom;
	assignTag("enemyspawner");
}

void OffenseBotSpawner::update(sf::Time& elapsed) {
	if (spawningTimer > 0) {
		spawningTimer -= elapsed.asMilliseconds();
	} else {
		OffenseBotPtr offenseBot_;
		sf::Vector2i iposition;
		if (spawnBotsOnBottom) { 
			iposition = sf::Vector2i(3, 26);
		} else {
			iposition = sf::Vector2i(3, 1);
		}
		
		offenseBot_ = std::make_shared<OffenseBot>(PlayingField::findAbsolutePosition(iposition), spawnBotsOnBottom, botType);
		GAME.getCurrentScene().addGameObject(offenseBot_);
		amount--;
		if (0 == amount) {
			makeDead();
		}
		spawningTimer = spawningDelay;
	}
	return;
}