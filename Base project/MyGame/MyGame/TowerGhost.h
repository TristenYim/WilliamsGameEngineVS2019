#pragma once

#include "Engine/GameEngine.h"
#include "Tower.h"

class TowerGhost : public GameObject {
public:
	TowerGhost();

	static void setType(TowerTypes neoType);
	static void setPosition(sf::Vector2f(neoPosition));
	static void setVisibility(bool neoVisibility);
	static bool isVisibile();
	static TowerTypes getType();

	void draw();
private:
	static sf::Sprite sprite_;
	static sf::Sprite rangeBox_;
	static bool visibility;
	static TowerTypes type_;
};

typedef std::shared_ptr<TowerGhost> TowerGhostPtr;