#pragma once

const int FIELD_GRID_SIDE_LENGTH = 32;
const int FIELD_MAP_BORDER_WIDTH = 10;
const int FIELD_GRID_WIDTH = 54;
const int FIELD_GRID_HEIGHT = 27;

#include "Engine/GameEngine.h"
#include "GameScene.h"

class PlayingField : public GameObject {
public:
	PlayingField();

	// Useful for ensuring objects do not leave the field
	sf::Vector2i findRelativePosition(sf::Vector2f absolutePosition);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
private:
	// Used as a reference point when adding objects
	sf::Sprite sprite_;
	sf::Vector2f topLeftCornerPos;

	// Use this for positioning objects relative to the field grid
	sf::Vector2f findAbsolutePosition(sf::Vector2i positionInGrid);

	// Use this to add objects to the current scene outside of update by adding it to this vector
	std::vector<GameObjectPtr> objectsToAdd;

	void addObstacle(sf::Vector2i positionInGrid, sf::Texture& texture_);
};

typedef std::shared_ptr<PlayingField> PlayingFieldPtr;