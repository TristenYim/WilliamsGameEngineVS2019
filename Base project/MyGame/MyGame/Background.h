#pragma once

#include "Engine/GameEngine.h"

class Background : public GameObject {
public:
	//Creates the scrolling background
	Background();
	//Game Object methods
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Sprite sprite_1;
	sf::Sprite sprite_2;
};

typedef std::shared_ptr<Background> BackgroundPtr;