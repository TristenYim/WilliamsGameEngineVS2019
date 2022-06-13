#include "PlayingField.h"
#include "SelectionBox.h"
#include "Obstacle.h"
#include <fstream>

// Defines (Don't know if that is the right word?) the static variables
sf::Vector2f PlayingField::topLeftCornerPos;
sf::Vector2f PlayingField::bottomRightCornerPos;
std::vector<std::vector<fieldGridBoxTypes>> PlayingField::obstacleMap;
std::vector<sf::Vector2i> PlayingField::squaresOccupiedByTowers;

PlayingField::PlayingField() {
	sprite_.setTexture(GAME.getTexture(FIELD_TEXTURE));
	sprite_.scale(2.0f, 2.0f);
	sprite_.setPosition(sf::Vector2f(topLeftCornerPos.x - FIELD_MAP_BORDER_WIDTH, topLeftCornerPos.y - FIELD_MAP_BORDER_WIDTH));
	assignTag("field");

	generateObstaclesFromFile(FIELD_MAP_FILE);

	SelectionBoxPtr selectionBox_ = std::make_shared<SelectionBox>(topLeftCornerPos);
	objectsToAdd.push_back(selectionBox_);
}

void PlayingField::initializeCornerPositions(sf::Vector2f itopLeftCornerPosition, sf::Vector2f ibottomRightCornerPosition) {
	topLeftCornerPos = itopLeftCornerPosition;
	bottomRightCornerPos = ibottomRightCornerPosition;
	return;
}

void PlayingField::addPositionToTowerPositions(sf::Vector2i relativePosition) {
	squaresOccupiedByTowers.push_back(relativePosition);
	return;
}

sf::Vector2i PlayingField::findRelativePosition(sf::Vector2f absolutePosition) {
	return sf::Vector2i(findRelativeXPosition(absolutePosition.x), findRelativeYPosition(absolutePosition.y));
}

int PlayingField::findRelativeXPosition(float absoluteXPosition) {
	if (topLeftCornerPos.x <= absoluteXPosition && bottomRightCornerPos.x >= absoluteXPosition) {
		return (int)(absoluteXPosition - topLeftCornerPos.x) / FIELD_GRID_SIDE_LENGTH;
	} else if (bottomRightCornerPos.x <= absoluteXPosition) {
		return OUTSIDE_OF_FIELD_DOWN_OR_RIGHT;
	} else {
		return OUTSIDE_OF_FIELD_UP_OR_LEFT;
	}
}

int PlayingField::findRelativeYPosition(float absoluteYPosition) {
	if (topLeftCornerPos.y <= absoluteYPosition && bottomRightCornerPos.y >= absoluteYPosition) {
		return (int)(absoluteYPosition - topLeftCornerPos.y) / FIELD_GRID_SIDE_LENGTH;
	} else if (bottomRightCornerPos.y <= absoluteYPosition) {
		return OUTSIDE_OF_FIELD_DOWN_OR_RIGHT;
	} else {
		return OUTSIDE_OF_FIELD_UP_OR_LEFT;
	}
}

sf::Vector2f PlayingField::findAbsolutePosition(sf::Vector2i positionInGrid) {
	return sf::Vector2f(findAbsoluteXPosition(positionInGrid.x), findAbsoluteYPosition(positionInGrid.y));
}

float PlayingField::findAbsoluteXPosition(int xPositionInGrid) {
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == xPositionInGrid) {
		return bottomRightCornerPos.x;
	} else if (OUTSIDE_OF_FIELD_UP_OR_LEFT == xPositionInGrid) {
		return topLeftCornerPos.x;
	} else {
		return topLeftCornerPos.x + xPositionInGrid * FIELD_GRID_SIDE_LENGTH;
	}
}

float PlayingField::findAbsoluteYPosition(int yPositionInGrid) {
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == yPositionInGrid) {
		return bottomRightCornerPos.y;
	} else if (OUTSIDE_OF_FIELD_UP_OR_LEFT == yPositionInGrid) {
		return topLeftCornerPos.y;
	} else {
		return topLeftCornerPos.y + yPositionInGrid * FIELD_GRID_SIDE_LENGTH;
	}
}

sf::Vector2f PlayingField::getTopLeftCornerPos() {
	return topLeftCornerPos;
}

sf::Vector2f PlayingField::getBottomRightCornerPos() {
	return bottomRightCornerPos;
}

bool PlayingField::canThisObjectBeAt(sf::Vector2i position, std::string tag) {
	if (position.y >= 0 && position.y < obstacleMap.size() && position.x >= 0 && position.x < obstacleMap[position.y].size()) {
		if ("defense" == tag) {
			switch (obstacleMap[position.y][position.x]) {
			case None:
				return false;
			default:
				return true;
			}
		} else if ("offense" == tag) {
			switch (obstacleMap[position.y][position.x]) {
			case All:
				return true;
			default:
				return false;
			}
		} else if ("tower" == tag) {
			switch (obstacleMap[position.y][position.x]) {
			case None:
				for (int index = 0; index < squaresOccupiedByTowers.size(); index++) {
					if (squaresOccupiedByTowers[index] == position) {
						return false;
					}
				}
				return true;
			default:
				return false;
			}
		}
	} else {
		return false;
	}
}

void PlayingField::update(sf::Time& elapsed) {
	while (objectsToAdd.size() > 0) {
		GAME.getCurrentScene().addGameObject(objectsToAdd[0]);
		objectsToAdd.erase(objectsToAdd.begin());
	}
	return;
}

sf::FloatRect PlayingField::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void PlayingField::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

void PlayingField::generateObstaclesFromFile(std::string filename) {
	std::ifstream mapFile;
	mapFile.open(filename);
	std::string mapFileLine;
	for (int row = -2; getline(mapFile, mapFileLine); row++) {
		if (row >= 0) {
			std::vector<fieldGridBoxTypes> obstacleMapRowToAdd;
			for (int collumn = 0; collumn < mapFileLine.size(); collumn++) {
				if ('1' == mapFileLine[collumn]) {
					addObstacle(sf::Vector2i(collumn, row));
					obstacleMapRowToAdd.push_back(None);
				} else if ('0' == mapFileLine[collumn]) {
					obstacleMapRowToAdd.push_back(All);
				} else {
					obstacleMapRowToAdd.push_back(DefenseOnly);
				}
			}
			obstacleMap.push_back(obstacleMapRowToAdd);
		}
	}
	mapFile.close();
	return;
}

void PlayingField::addObstacle(sf::Vector2i positionInGrid) {
	ObstaclePtr obstacle_ = std::make_shared<Obstacle>(findAbsolutePosition(positionInGrid));
	objectsToAdd.push_back(obstacle_);
	return;
}