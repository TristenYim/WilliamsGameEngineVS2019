#pragma once

#include "Engine/GameEngine.h"

class GameOverScene : public Scene {
public:
	//Creates the scene
	GameOverScene(int score);
private:
	std::string tag;
};

typedef std::shared_ptr<GameOverScene> GameOverScenePtr;