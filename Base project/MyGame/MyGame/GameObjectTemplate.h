#pragma once

#include "Engine/GameEngine.h"

// Replace "MyObject" with the name of your object

class MyObject : public GameObject {
public:
	MyObject(sf::Vector2f ipos, sf::Texture texture_);

	void draw();
};

typedef std::shared_ptr<MyObject> MyObjectPtr;