#pragma once

#include "Engine/GameEngine.h"

class TowerGhost : public GameObject {
public:
	TowerGhost(sf::Vector2f ipos, sf::Texture texture_);

	void draw();
};

typedef std::shared_ptr<TowerGhost> TowerGhostPtr;