#include "Background.h"

const float SCROLL_SPEED = 0.5f;

Background::Background() {
	sf::Sprite tempSprite_;
	tempSprite_.setTexture(GAME.getTexture("Resources/background.png"));
	float posx = 0;
	for (int repetitions = 0; 2 > repetitions; repetitions++) {
		float posy = 540;
		for (int repetitions2 = 0; 3 > repetitions2; repetitions2++) {
			tempSprite_.setPosition(posx, posy);
			sprites.push_back(tempSprite_);
			posy -= 540;
		}
		posx = 961;
	}
	assignTag("background");
}

void Background::draw() {
	for (int index = 0; sprites.size() > index; index++) {
		GAME.getRenderWindow().draw(sprites[index]);
	}
	return;
}

void Background::update(sf::Time& elapsed) {
	int msElapsed = elapsed.asMilliseconds();
	for (int index = 0; sprites.size() > index; index++) {
		sf::Vector2f currentSpritePos = sprites[index].getPosition();
		currentSpritePos.y += SCROLL_SPEED * msElapsed;
		if (GAME.getRenderWindow().getSize().y < currentSpritePos.y) {
			currentSpritePos.y -= GAME.getRenderWindow().getSize().y + 540;
		}
		sprites[index].setPosition(currentSpritePos);
	}
	return;
}