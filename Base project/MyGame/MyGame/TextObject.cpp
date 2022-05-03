#include "TextObject.h"

void TextObject::setupText(sf::Vector2f pos, int charSize, sf::Color textColor) {
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(pos);
	text_.setCharacterSize(charSize);
	text_.setFillColor(textColor);
	return;
}

void TextObject::draw() {
	GAME.getRenderWindow().draw(text_);
	return;
}