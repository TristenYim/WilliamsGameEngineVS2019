#include "SelectionBox.h"
#include "PlayingField.h"
#include "Credits.h"
#include "Tower.h"
#include "TowerGhost.h"
#include <sstream>

SelectionBox::SelectionBox(sf::Vector2f ipos, sf::Vector2f itextPos, int icharSize, sf::Color itextColor) {
	sprite_.setPosition(ipos);
	sprite_.setTexture(GAME.getTexture("Resources/Selection Box.png"));
	setupText(itextPos, icharSize, itextColor);
	assignTag("selection");
}

void SelectionBox::update(sf::Time& elapsed) {
	std::stringstream stream;
	if (PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(sprite_.getPosition()), "towerupgradebox")) {
		stream << "Upgrade Cost: ";
	} else if (TowerGhost::isVisibile() && PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(sprite_.getPosition()), "tower")) {
		stream << "Tower Cost: " << Tower::getCost(TowerGhost::getType());
	}
	text_.setString(stream.str());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !pressedM) {
		mouseControlsEnabled = !mouseControlsEnabled;
		pressedM = true;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		pressedM = true;
	} else {
		pressedM = false;
	}

	towerActions();
	updateColorAndAnimation(elapsed.asMilliseconds());
	updatePosition(elapsed.asMilliseconds());
	return;
}

void SelectionBox::draw() {
	GAME.getRenderWindow().draw(sprite_);
	GAME.getRenderWindow().draw(text_);
	return;
}

sf::FloatRect SelectionBox::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void SelectionBox::towerActions() {
	if (TowerGhost::isVisibile) {
		TowerGhost::setPosition(sf::Vector2f(sprite_.getPosition().x + sprite_.getGlobalBounds().width / 2.0, sprite_.getPosition().y + sprite_.getGlobalBounds().height / 2.0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		TowerGhost::setType(CheesyPoofs);
		TowerGhost::setVisibility(true);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		TowerGhost::setType(SonicSquirrels);
		TowerGhost::setVisibility(true);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		TowerGhost::setVisibility(false);
	}

	if (TowerGhost::isVisibile() && sf::Keyboard::isKeyPressed(sf::Keyboard::B) && Credits::getCredit() >= Tower::getCost(TowerGhost::getType()) &&
		PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(sprite_.getPosition()), "tower"))
	{
		PlayingField::addPositionToTowerPositions(PlayingField::findRelativePosition(sprite_.getPosition()));
		TowerPtr tower_ = std::make_shared<Tower>(TowerGhost::getType(), sf::Vector2f(sprite_.getPosition().x + sprite_.getGlobalBounds().width / 2.0, sprite_.getPosition().y + sprite_.getGlobalBounds().height / 2.0));
		GAME.getCurrentScene().addGameObject(tower_);
		Credits::addCredit(-Tower::getCost(TowerGhost::getType()));
	}
}

void SelectionBox::updateColorAndAnimation(float msElapsed) {
	animationTimer -= msElapsed;
	sf::Color spriteColor = sprite_.getColor();
	if (animationTimer >= TIME_BUFFER + FADE_OUT_TIME + FADE_IN_TIME) {
		sprite_.setColor(sf::Color(spriteColor.r, spriteColor.g, spriteColor.b, 255));
	} else if (animationTimer >= TIME_BUFFER + FADE_IN_TIME) {
		sprite_.setColor(sf::Color(spriteColor.r, spriteColor.g, spriteColor.b, (animationTimer - TIME_BUFFER - FADE_IN_TIME) / FADE_OUT_TIME * 255));
	} else if (animationTimer >= TIME_BUFFER) {
		sprite_.setColor(sf::Color(spriteColor.r, spriteColor.g, spriteColor.b, (TIME_BUFFER + FADE_IN_TIME - animationTimer) / FADE_IN_TIME * 255));
	} else {
		animationTimer += SOLID_TIME + FADE_IN_TIME + FADE_OUT_TIME;
	}

	if (PlayingField::canThisObjectBeAt(PlayingField::findRelativePosition(sprite_.getPosition()), "tower")) {
		sprite_.setColor(sf::Color(0, 95, 168, sprite_.getColor().a));
	} else if (sprite_.getColor() != sf::Color(226, 12, 16, sprite_.getColor().a)) {
		sprite_.setColor(sf::Color(226, 12, 16, sprite_.getColor().a));
	}
}

void SelectionBox::updatePosition(float msElapsed) {
	sf::Vector2f neoPosition;
	if (mouseControlsEnabled) {
		sf::Vector2i cursorPosition = PlayingField::findRelativePosition((sf::Vector2f)sf::Mouse::getPosition(GAME.getRenderWindow()));
		neoPosition = PlayingField::findAbsolutePosition(cursorPosition);
		if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == cursorPosition.x) {
			neoPosition.x -= sprite_.getGlobalBounds().width;
		}
		if (OUTSIDE_OF_FIELD_DOWN_OR_RIGHT == cursorPosition.y) {
			neoPosition.y -= sprite_.getGlobalBounds().height;
		}
	} else {
		neoPosition = sprite_.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (arrowKeyTimer == ARROW_KEY_DELAY || arrowKeyTimer < ARROW_KEY_DELAY - ARROW_KEY_SUPER_SPEED_DELAY) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && PlayingField::findRelativePosition(sprite_.getPosition()).y != 0) {
					neoPosition.y -= FIELD_GRID_SIDE_LENGTH;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && PlayingField::findRelativePosition(sprite_.getPosition()).x != FIELD_GRID_WIDTH - 1) {
					neoPosition.x += FIELD_GRID_SIDE_LENGTH;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && PlayingField::findRelativePosition(sprite_.getPosition()).y != FIELD_GRID_HEIGHT - 1) {
					neoPosition.y += FIELD_GRID_SIDE_LENGTH;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && PlayingField::findRelativePosition(sprite_.getPosition()).x != 0) {
					neoPosition.x -= FIELD_GRID_SIDE_LENGTH;
				}
				if (arrowKeyTimer < ARROW_KEY_DELAY - ARROW_KEY_SUPER_SPEED_DELAY) {
					arrowKeyTimer += msElapsed;
				}
			}
			arrowKeyTimer -= msElapsed;
		} else {
			arrowKeyTimer = ARROW_KEY_DELAY;
		}
	}
	sprite_.setPosition(neoPosition);
}