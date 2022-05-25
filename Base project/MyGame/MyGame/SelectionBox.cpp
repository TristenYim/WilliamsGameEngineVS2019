#include "SelectionBox.h"
#include "GameScene.h"
#include "PlayingField.h"
#include "Tower.h"

SelectionBox::SelectionBox(sf::Vector2f ipos) {
	sprite_.setPosition(ipos);
	sprite_.setTexture(GAME.getTexture("Resources/Selection Box.png"));
	setCollisionCheckEnabled(true);
	assignTag("selection");
}

void SelectionBox::update(sf::Time& elapsed) {
	animationTimer -= elapsed.asMilliseconds();
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

	GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();
	PlayingFieldPtr playingField_ = (PlayingFieldPtr&)currentScene_.getGameObject("field");

	sf::Vector2f neoPosition;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		mouseControlsEnabled = !mouseControlsEnabled;
	}

	if (mouseControlsEnabled) {
		sf::Vector2i cursorPosition = playingField_->findRelativePosition((sf::Vector2f)sf::Mouse::getPosition(GAME.getRenderWindow()));
		neoPosition = playingField_->findAbsolutePosition(cursorPosition);
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playingField_->findRelativePosition(sprite_.getPosition()).y != 0) {
					neoPosition.y -= 32.0f;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playingField_->findRelativePosition(sprite_.getPosition()).x != FIELD_GRID_WIDTH - 1) {
					neoPosition.x += 32.0f;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playingField_->findRelativePosition(sprite_.getPosition()).y != FIELD_GRID_HEIGHT - 1) {
					neoPosition.y += 32.0f;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playingField_->findRelativePosition(sprite_.getPosition()).x != 0) {
					neoPosition.x -= 32.0f;
				}
				if (arrowKeyTimer < ARROW_KEY_DELAY - ARROW_KEY_SUPER_SPEED_DELAY) {
					arrowKeyTimer += elapsed.asMilliseconds();
				}
			}
			arrowKeyTimer -= elapsed.asMilliseconds();
		} else {
			arrowKeyTimer = ARROW_KEY_DELAY;
		}
	}
	sprite_.setPosition(neoPosition);

	if (playingField_->canThisObjectBeAt(playingField_->findRelativePosition(sprite_.getPosition()), "tower") && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		TowerPtr tower_ = std::make_shared<Tower>(sprite_.getPosition());
		currentScene_.addGameObject(tower_);
	}
	return;
}

void SelectionBox::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

sf::FloatRect SelectionBox::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void SelectionBox::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("obstacle") && sprite_.getColor() != sf::Color(0, 95, 158)) {
		sprite_.setColor(sf::Color(0, 95, 168));
	} else if (sprite_.getColor() != sf::Color(226, 12, 16)) {
		sprite_.setColor(sf::Color(226, 12, 16));
	}
	return;
}