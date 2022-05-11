#pragma once

#include "Engine/GameEngine.h"
#include "GameScene.h"

class PlayingField : public GameObject {
public:
	PlayingField();

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
private:
	// Used as a reference point when adding objects
	sf::Vector2f topLeftCornerPos;
	sf::Sprite sprite_;

	// Used to ensure pressing the arrow keys only moves the selection box once per press
	bool movedSelectionBox = false;

	// Use this for positioning objects relative to the field grid
	sf::Vector2f findAbsolutePositionOfObject(sf::Vector2i positionInGrid);

	// Useful for ensuring objects do not leave the field
	sf::Vector2i findRelativePositionOfObject(sf::Vector2f absolutePosition);

	// Use this to add objects to the current scene outside of update by adding it to this vector
	std::vector<GameObjectPtr> objectsToAdd;

	void addObstacle(sf::Vector2i positionInGrid, sf::Texture& texture_);
};

typedef std::shared_ptr<PlayingField> PlayingFieldPtr;