#pragma once

#include "Engine/GameEngine.h"

class GameScene : public Scene {
public:
	GameScene();

	// Use this to find a specific object with a specific tag
	GameObjectPtr getGameObject(std::string tag);
};

typedef std::shared_ptr<GameScene> GameScenePtr;