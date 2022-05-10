#pragma once

#include "Engine/GameEngine.h"
#include "Obstacle.h"

class PlayingField : public GameObject {
public:
	// Creates the obstacle
	PlayingField();

	// Methods overriden from GameObject
	void draw();
private:
	sf::Sprite sprite_;
	
	// The field is divided into a 54x27 grid of 32x32 pixel squares
	// Most objects on the field take up one of these squares
	// The method below is used to internally calculate the absolution position of an object when given the position in the grid
	// This is so objects can be consistently placed in the center of grid squares
	
	sf::Vector2f findAbsolutePositionOfObject(sf::Vector2i positionInGrid);
	
	// To ensure the code looks clean, the game field stores obstacel internally

	std::vector<Obstacle> obstacles;
	void addObstacle(sf::Vector2i positionInGrid, sf::Texture texture_);
};

typedef std::shared_ptr<PlayingField> PlayingFieldPtr;