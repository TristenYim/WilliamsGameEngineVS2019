#pragma once

#include "Engine/GameEngine.h"

class GoodLuck : public GameObject {
public:
	//Creates the text
	GoodLuck();

	//Changes the color of the text
	void changeColor(sf::Color);

	//Methods overriden from GameObject
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text goodLuckText_;
};