#pragma once

#include "Engine/GameEngine.h"

class GameOverScene : public Scene {
public:
	GameOverScene();
};

typedef std::shared_ptr<GameOverScene> GameOverScenePtr;