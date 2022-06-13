#include "OffenseBotSpawner.h"
#include "OffenseBot.h";
#include "PlayingField.h"

OffenseBotSpawner::OffenseBotSpawner(float ispawningDelay, float ibotMovementSpeed) {
	spawningDelay = ispawningDelay;
	spawningTimer = ispawningDelay;
	botMovemevntSpeed = ibotMovementSpeed;
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
		offenseBot_ = std::make_shared<OffenseBot>(PlayingField::findAbsolutePosition(iposition), botMovemevntSpeed, spawnBotsOnBottom, 50, 1000);
		GAME.getCurrentScene().addGameObject(offenseBot_);
		spawnBotsOnBottom = !spawnBotsOnBottom;
		spawningTimer = spawningDelay;
	}
	return;
}