#include "SelectionBox.h"
#include "GameScene.h"
#include "PlayingField.h"

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

	GameScene currentScene_ = (GameScene&)GAME.getCurrentScene();
	PlayingFieldPtr playingField_ = (PlayingFieldPtr&)currentScene_.getGameObject("field");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (arrowKeyTimer == 1000 || arrowKeyTimer < 250) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playingField_->findRelativePosition(sprite_.getPosition()).y != 0)							sprite_.move(sf::Vector2f(0.0f, -32.0f));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playingField_->findRelativePosition(sprite_.getPosition()).x != FIELD_GRID_WIDTH - 1)	sprite_.move(sf::Vector2f(32.0f, 0.0f));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playingField_->findRelativePosition(sprite_.getPosition()).y != FIELD_GRID_HEIGHT - 1)	sprite_.move(sf::Vector2f(0.0f, 32.0f));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playingField_->findRelativePosition(sprite_.getPosition()).x != 0)						sprite_.move(sf::Vector2f(-32.0f, 0.0f));
			if (arrowKeyTimer < 500) {
				arrowKeyTimer += elapsed.asMilliseconds() * 5;
			}
		}
		arrowKeyTimer -= elapsed.asMilliseconds();
	} else {
		arrowKeyTimer = 1000;
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
	if (otherGameObject.hasTag("obstacle")) {
		sprite_.setColor(sf::Color(0, 95, 168));
	} else {
		sprite_.setColor(sf::Color(226, 12, 16));
	}
	return;
}