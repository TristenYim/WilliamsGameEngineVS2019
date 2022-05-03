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
	std::vector<sf::Sprite> sprites;
};

typedef std::shared_ptr<Background> BackgroundPtr;