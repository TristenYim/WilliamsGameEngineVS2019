#pragma once

#include "Engine/GameEngine.h"

class GoodLuck : public TextObject {
public:
	//Creates the text
	GoodLuck();

	//Changes the color of the text
	void changeColor(sf::Color);

	//Methods overriden from GameObject
	void update(sf::Time& elapsed);
};

typedef std::shared_ptr<GoodLuck> GoodLuckTextPtr;