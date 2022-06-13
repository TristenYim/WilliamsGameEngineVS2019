#pragma once

#include "Engine/GameEngine.h"

class EndingScene : public Scene {
public:
	EndingScene(bool didThePlayerWin);
};

typedef std::shared_ptr<EndingScene> EndingScenePtr;