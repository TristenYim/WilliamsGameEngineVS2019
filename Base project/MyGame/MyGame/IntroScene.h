#pragma once

#include "Engine/GameEngine.h"

class IntroScene : public Scene {
public:
	IntroScene();
};

typedef std::shared_ptr<IntroScene> IntroScenePtr;