#pragma once

const int FIELD_GRID_SIDE_LENGTH = 32;
const int FIELD_MAP_BORDER_WIDTH = 10;
const int FIELD_GRID_WIDTH = 54;
const int FIELD_GRID_HEIGHT = 27;
const int OUTSIDE_OF_FIELD_DOWN_OR_RIGHT = 254;
const int OUTSIDE_OF_FIELD_UP_OR_LEFT = 148;

#include "Engine/GameEngine.h"
#include "GameScene.h"

class PlayingField : public GameObject {
public:
	PlayingField();

	// Useful for ensuring objects do not leave the field
	sf::Vector2i findRelativePosition(sf::Vector2f absolutePosition);

	// Use this for positioning objects relative to the field grid
	sf::Vector2f findAbsolutePosition(sf::Vector2i positionInGrid);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
private:
	// Used as a reference point when adding objects
	sf::Vector2f topLeftCornerPos;
	sf::Vector2f bottomRightCornerPos;

	// Used to generate the obstacles from a file since placing each individual obstacle with code would be difficult to read
	void generateObstaclesFromFile(std::string filename);

	// Use this to add objects to the current scene outside of update by adding it to this vector
	std::vector<GameObjectPtr> objectsToAdd;

	void addObstacle(sf::Vector2i positionInGrid);
};

typedef std::shared_ptr<PlayingField> PlayingFieldPtr;