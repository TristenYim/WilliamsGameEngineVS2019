#pragma once

#include "Engine/GameEngine.h"

class TextObject : public GameObject {
public:
	//Methods overriden from GameObject
	void draw();
protected:
	//Sets the position, font, font size, and font color of the text
	void setupText(sf::Vector2f pos, int charSize, sf::Color textColor);
	sf::Text text_;
};

typedef std::shared_ptr<TextObject> TextObjectPtr;