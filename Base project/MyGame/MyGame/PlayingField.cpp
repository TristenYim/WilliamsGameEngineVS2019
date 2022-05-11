#include "PlayingField.h"
#include "SelectionBox.h"
#include "Obstacle.h"

const int FIELD_GRID_SIDE_LENGTH = 32;
const int FIELD_MAP_BORDER_WIDTH = 10;
const int FIELD_GRID_WIDTH = 54;
const int FIELD_GRID_HEIGHT = 27;

PlayingField::PlayingField() {
	sprite_.setTexture(GAME.getTexture("Resources/Field Boundary.png"));
	sprite_.scale(2.0f, 2.0f);

	topLeftCornerPos.x = GAME.getRenderWindow().getSize().x / 2.0f - sprite_.getTextureRect().width + FIELD_MAP_BORDER_WIDTH;
	topLeftCornerPos.y = GAME.getRenderWindow().getSize().y / 2.0f - sprite_.getTextureRect().height + FIELD_MAP_BORDER_WIDTH;

	sprite_.setPosition(sf::Vector2f(topLeftCornerPos.x - FIELD_MAP_BORDER_WIDTH, topLeftCornerPos.y - FIELD_MAP_BORDER_WIDTH));
	assignTag("field");

	SelectionBoxPtr selectionBox_ = std::make_shared<SelectionBox>(topLeftCornerPos);
	objectsToAdd.push_back(selectionBox_);

	// Temp code for testing obstacles
	for (int repetitions = 0; repetitions < 9; repetitions++) {
		addObstacle(sf::Vector2i(0, repetitions * 3), GAME.getTexture("Resources/Red Square.png"));
		addObstacle(sf::Vector2i(0, repetitions * 3 + 1), GAME.getTexture("Resources/Green Square.png"));
		addObstacle(sf::Vector2i(0, repetitions * 3 + 2), GAME.getTexture("Resources/Yellow Square.png"));
	}
}

void PlayingField::update(sf::Time& elapsed) {
	if (objectsToAdd.size() > 0) {
		GAME.getCurrentScene().addGameObject(objectsToAdd[0]);
		objectsToAdd.erase(objectsToAdd.begin());
	}

	GameScene& CurrentScene = (GameScene&)GAME.getCurrentScene();
	SelectionBoxPtr currentSelectionBox_ = (SelectionBoxPtr&)CurrentScene.getGameObject("selection");
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!movedSelectionBox) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && findRelativePositionOfObject(currentSelectionBox_->getPosition()).y != 0)						currentSelectionBox_->addToPosition(sf::Vector2f(0.0f, -32.0f));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && findRelativePositionOfObject(currentSelectionBox_->getPosition()).x != FIELD_GRID_WIDTH - 1)	currentSelectionBox_->addToPosition(sf::Vector2f(32.0f, 0.0f));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && findRelativePositionOfObject(currentSelectionBox_->getPosition()).y != FIELD_GRID_HEIGHT - 1)	currentSelectionBox_->addToPosition(sf::Vector2f(0.0f, 32.0f));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && findRelativePositionOfObject(currentSelectionBox_->getPosition()).x != 0)						currentSelectionBox_->addToPosition(sf::Vector2f(-32.0, 0.0f));
		}
		movedSelectionBox = true;
	} else {
		movedSelectionBox = false;
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

sf::Vector2f PlayingField::findAbsolutePositionOfObject(sf::Vector2i positionInGrid) {
	float posx = topLeftCornerPos.x + positionInGrid.x * FIELD_GRID_SIDE_LENGTH;
	float posy = topLeftCornerPos.y + positionInGrid.y * FIELD_GRID_SIDE_LENGTH;
	return sf::Vector2f(posx, posy);
}

sf::Vector2i PlayingField::findRelativePositionOfObject(sf::Vector2f absolutePosition) {
	int posx = (int)(absolutePosition.x - topLeftCornerPos.x) / FIELD_GRID_SIDE_LENGTH;
	int posy = (int)(absolutePosition.y - topLeftCornerPos.y) / FIELD_GRID_SIDE_LENGTH;
	return sf::Vector2i(posx, posy);
}

void PlayingField::addObstacle(sf::Vector2i positionInGrid, sf::Texture& texture_) {
	ObstaclePtr obstacle_ = std::make_shared<Obstacle>(findAbsolutePositionOfObject(positionInGrid), texture_);
	objectsToAdd.push_back(obstacle_);
	return;
}