#include "PlayingField.h"
#include "SelectionBox.h"
#include "Obstacle.h"
#include <fstream>

sf::Vector2f PlayingField::topLeftCornerPos;
sf::Vector2f PlayingField::bottomRightCornerPos;

PlayingField::PlayingField() {
	sprite_.setTexture(GAME.getTexture(FIELD_TEXTURE));
	sprite_.scale(2.0f, 2.0f);
	sprite_.setPosition(sf::Vector2f(topLeftCornerPos.x - FIELD_MAP_BORDER_WIDTH, topLeftCornerPos.y - FIELD_MAP_BORDER_WIDTH));
	assignTag("field");

	generateObstaclesFromFile(OBSTACLE_FIELD_MAP_FILE_NAME);

	SelectionBoxPtr selectionBox_ = std::make_shared<SelectionBox>(topLeftCornerPos);
	objectsToAdd.push_back(selectionBox_);
}

void PlayingField::initializeCornerPositions(sf::Vector2f itopLeftCornerPosition, sf::Vector2f ibottomRightCornerPosition) {
	topLeftCornerPos = itopLeftCornerPosition;
	bottomRightCornerPos = ibottomRightCornerPosition;
	return;
}

sf::Vector2i PlayingField::findRelativePosition(sf::Vector2f absolutePosition) {
	int posx;
	int posy;
	if (topLeftCornerPos.x <= absolutePosition.x && bottomRightCornerPos.x >= absolutePosition.x) {
		posx = (int)(absolutePosition.x - topLeftCornerPos.x) / FIELD_GRID_SIDE_LENGTH;
	} else if (bottomRightCornerPos.x <= absolutePosition.x) {
		posx = OUTSIDE_OF_FIELD_DOWN_OR_RIGHT;
	} else {
		posx = OUTSIDE_OF_FIELD_UP_OR_LEFT;
	}
	if (topLeftCornerPos.y <= absolutePosition.y && bottomRightCornerPos.y >= absolutePosition.y) {
		posy = (int)(absolutePosition.y - topLeftCornerPos.y) / FIELD_GRID_SIDE_LENGTH;
	} else if (bottomRightCornerPos.y <= absolutePosition.y) {
		posy = OUTSIDE_OF_FIELD_DOWN_OR_RIGHT;
	} else {
		posy = OUTSIDE_OF_FIELD_UP_OR_LEFT;
	}
	return sf::Vector2i(posx, posy);
}

sf::Vector2f PlayingField::findAbsolutePosition(sf::Vector2i positionInGrid) {
	float posx;
	float posy;
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == positionInGrid.x) {
		posx = bottomRightCornerPos.x;
	} else if (OUTSIDE_OF_FIELD_UP_OR_LEFT == positionInGrid.x) {
		posx = topLeftCornerPos.x;
	} else {
		posx = topLeftCornerPos.x + positionInGrid.x * FIELD_GRID_SIDE_LENGTH;
	}
	if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == positionInGrid.y) {
		posy = bottomRightCornerPos.y;
	} else if (OUTSIDE_OF_FIELD_UP_OR_LEFT == positionInGrid.y) {
		posy = topLeftCornerPos.y;
	} else {
		posy = topLeftCornerPos.y + positionInGrid.y * FIELD_GRID_SIDE_LENGTH;
	}
	return sf::Vector2f(posx, posy);
}

bool PlayingField::canThisObjectBeAt(sf::Vector2i position, std::string tag) {
	if (position.y <= obstacleMap.size() && position.x <= obstacleMap[position.y].size()) {
		if ("defense" == tag) {
			switch (obstacleMap[position.y][position.x]) {
			case None:
				return true;
			default:
				return false;
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
	for (int row = 0; getline(mapFile, mapFileLine); row++) {
		std::vector<fieldGridBoxTypes> obstacleMapRowToAdd;
		for (int collumn = 0; collumn < mapFileLine.size(); collumn++) {
			if ('1' == mapFileLine[collumn]) {
				addObstacle(sf::Vector2i(collumn, row));
				obstacleMapRowToAdd.push_back(None);
			} else if ('0' == mapFileLine[collumn]) {
				obstacleMapRowToAdd.push_back(All);
			} else {
				obstacleMapRowToAdd.push_back(OffenseOnly);
			}
		}
		obstacleMap.push_back(obstacleMapRowToAdd);
	}
	mapFile.close();
	return;
}

void PlayingField::addObstacle(sf::Vector2i positionInGrid) {
	ObstaclePtr obstacle_ = std::make_shared<Obstacle>(findAbsolutePosition(positionInGrid));
	objectsToAdd.push_back(obstacle_);
	return;
}