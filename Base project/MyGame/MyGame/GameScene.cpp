#include "GameScene.h"
#include "PlayingField.h"
#include "DefenseBot.h"
#include "OffenseBotSpawner.h"
#include "OffenseBot.h"

GameScene::GameScene() {

	// Format for adding an object:
	// MyObjectPtr myObject_ = std::make_shared<MyObject>( arguments );
	// addGameObject(myObject_);

	// I'm not sure if the engine or SFML can just read the dimensions of an image, so I'm just creating a temporary Sprite to figure it out.
	sf::Sprite tempSprite_;
	tempSprite_.setTexture(GAME.getTexture(FIELD_TEXTURE));

	sf::Vector2f fieldTopLeftCornerPosition;
	fieldTopLeftCornerPosition.x = GAME.getRenderWindow().getSize().x / 2.0f - tempSprite_.getTextureRect().width + FIELD_MAP_BORDER_WIDTH;
	fieldTopLeftCornerPosition.y = GAME.getRenderWindow().getSize().y / 2.0f - tempSprite_.getTextureRect().height + FIELD_MAP_BORDER_WIDTH;
	sf::Vector2f fieldBottomRightCornerPosition;
	fieldBottomRightCornerPosition.x = GAME.getRenderWindow().getSize().x / 2.0f + tempSprite_.getTextureRect().width - FIELD_MAP_BORDER_WIDTH;
	fieldBottomRightCornerPosition.y = GAME.getRenderWindow().getSize().y / 2.0f + tempSprite_.getTextureRect().height - FIELD_MAP_BORDER_WIDTH;

	PlayingField::initializeCornerPositions(fieldTopLeftCornerPosition, fieldBottomRightCornerPosition);

	PlayingFieldPtr playingField_ = std::make_shared<PlayingField>();
	addGameObject(playingField_);
	DefenseBotPtr defenseBot_ = std::make_shared<DefenseBot>(PlayingField::findAbsolutePosition(sf::Vector2i(48, 14)));
	addGameObject(defenseBot_);
	OffenseBotSpawnerPtr offenseBotSpawner_ = std::make_shared<OffenseBotSpawner>(10000, 0.05);
	addGameObject(offenseBotSpawner_);
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