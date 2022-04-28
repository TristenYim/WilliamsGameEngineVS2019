#pragma once

#include "Engine/GameEngine.h"

class GameScene : public Scene {
public:
	// Creates our Scene.
	GameScene();
	int getScore();
	//Increases the score by the given amount, or 1 by default
	void increaseScore();
	void increaseScore(int additive);
	int getLives();
	//Decreases lives by the given amount, or 1 by default.
	void decreaseLives();
	void decreaseLives(int subtractor);
private:
	int score_ = 0;
	int lives_ = 10;
	//Checks the amount of lives. Transitions to GameOverScene if none remain.
	void checkForGameOver();
};

typedef std::shared_ptr<GameScene> GameScenePtr;