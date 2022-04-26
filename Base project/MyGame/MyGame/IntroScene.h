#pragma once

#include "Engine/GameEngine.h"

class IntroScene : public Scene {
public:
	//Creates our scene
	IntroScene();
};

typedef std::shared_ptr<IntroScene> IntroScenePtr;