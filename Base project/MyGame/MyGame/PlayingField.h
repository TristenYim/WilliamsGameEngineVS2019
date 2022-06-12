#pragma once

#include "Engine/GameEngine.h"

const int FIELD_GRID_SIDE_LENGTH = 32;
const int FIELD_MAP_BORDER_WIDTH = 10;
const int FIELD_GRID_WIDTH = 54;
const int FIELD_GRID_HEIGHT = 27;
const int OUTSIDE_OF_FIELD_UP_OR_LEFT = 254;
const int OUTSIDE_OF_FIELD_DOWN_OR_RIGHT = 1690;
const std::string FIELD_TEXTURE = "Resources/Field Boundary.png";
const std::string FIELD_MAP_FILE = "Obstacle Field Map.txt";

enum fieldGridBoxTypes { All = 0, None = 1, DefenseOnly = 2 };

class PlayingField : public GameObject {
public:
	//		Constructors/Setup
	PlayingField();

	// Initializing the corner positions is required to use the static methods below
	static void initializeCornerPositions(sf::Vector2f itopLeftCornerPosition, sf::Vector2f itopRightCornerPosition);

	//		Setters/Adders
	static void addPositionToTowerPositions(sf::Vector2i relatievPosition);

	//		Methods
	// Useful for ensuring objects do not leave the field
	static sf::Vector2i findRelativePosition(sf::Vector2f absolutePosition);
	static int findRelativeXPosition(float absoluteXPosition);
	static int findRelativeYPosition(float absoluteYPosition);

	// Use this for positioning objects relative to the field grid
	static sf::Vector2f findAbsolutePosition(sf::Vector2i positionInGrid);
	static float findAbsoluteXPosition(int xPositionInGrid);
	static float findAbsoluteYPosition(int yPositionInGrid);

	// Used to check a field-relative position for obstacles by looking at the obstacle generation file. It checks the file because searching every game object is slow
	static bool canThisObjectBeAt(sf::Vector2i position, std::string tag);

	//		Methods overriden from GameObject
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
private:
	//		Variables
	// Used as a reference point when adding objects
	static sf::Vector2f topLeftCornerPos;
	static sf::Vector2f bottomRightCornerPos;

	// Used to store the obstacle map
	static std::vector<std::vector<fieldGridBoxTypes>> obstacleMap;

	// Used to store locations where towers are so multiple towers aren't placed on the same square
	static std::vector<sf::Vector2i> squaresOccupiedByTowers;

	// Use this to add objects to the current scene outside of update by adding it to this vector
	std::vector<GameObjectPtr> objectsToAdd;

	//		Methods
	// The obstacles generate from a file and are stored in a 2d vector since that is the easiset way to read and edit the position of obstacles
	void generateObstaclesFromFile(std::string filename);

	void addObstacle(sf::Vector2i positionInGrid);
};

typedef std::shared_ptr<PlayingField> PlayingFieldPtr;