#include "GameScene.h"
#include "PlayingField.h"

GameScene::GameScene() {

	// Format for adding an object:
	// MyObjectPtr myObject_ = std::make_shared<MyObject>( arguments );
	// addGameObject(myObject_);

	PlayingFieldPtr playingField_ = std::make_shared <PlayingField>();
	addGameObject(playingField_);
}