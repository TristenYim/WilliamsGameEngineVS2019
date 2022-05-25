#include "GameScene.h"
#include "PlayingField.h"
#include "DefenseBot.h"
#include "OffenseBot.h"

GameScene::GameScene() {

	// Format for adding an object:
	// MyObjectPtr myObject_ = std::make_shared<MyObject>( arguments );
	// addGameObject(myObject_);

	PlayingFieldPtr playingField_ = std::make_shared<PlayingField>();
	addGameObject(playingField_);
	DefenseBotPtr defenseBot_ = std::make_shared<DefenseBot>(playingField_->findAbsolutePosition(sf::Vector2i(48, 14)));
	addGameObject(defenseBot_);
	OffenseBotPtr offenseBot_ = std::make_shared<OffenseBot>(playingField_->findAbsolutePosition(sf::Vector2i(3, 1)), 0.3);
	addGameObject(offenseBot_);
}

GameObjectPtr GameScene::getGameObject(std::string tag) {
	int currentObject = 0;
	for (auto & gameObject : gameObjects_) {
		if (gameObject->hasTag(tag)) {
			return gameObject;
		}
		currentObject++;
	}
}