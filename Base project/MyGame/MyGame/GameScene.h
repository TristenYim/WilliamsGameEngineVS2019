#pragma once

#include "Engine/GameEngine.h"

class GameScene : public Scene {
public:
	// Creates our Scene.
	GameScene();
	int getScore();
	//If increaseScore is called with arguments, it adds the additive to the score. Otherwise, it increases the score by one.
	void increaseScore();
	void increaseScore(int additive);
private:
	int score_ = 0;
};

typedef std::shared_ptr<GameScene> GameScenePtr;