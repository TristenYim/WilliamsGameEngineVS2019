#include "OffenseBotSpawner.h"
#include "OffenseBot.h";
#include "PlayingField.h"

OffenseBotSpawner::OffenseBotSpawner(float ispawningDelay) {
	spawningDelay = ispawningDelay;
	spawningTimer = ispawningDelay;
	assignTag("enemyspawner");
}

void OffenseBotSpawner::update(sf::Time& elapsed) {
	if (spawningTimer > 0) {
		spawningTimer -= elapsed.asMilliseconds();
	} else {
		OffenseBotPtr offenseBot_;
		if (spawnBotsOnBottom) {
			offenseBot_ = std::make_shared<OffenseBot>(PlayingField::findAbsolutePosition(sf::Vector2i(3, 26)), 0.1f, true);
		} else {
			offenseBot_ = std::make_shared<OffenseBot>(PlayingField::findAbsolutePosition(sf::Vector2i(3, 1)), 0.1f, false);
		}
		GAME.getCurrentScene().addGameObject(offenseBot_);
		spawnBotsOnBottom = !spawnBotsOnBottom;
		spawningTimer = spawningDelay;
	}
	return;
}