#pragma once

#include "Engine/GameEngine.h"

// Replace "MyObject" with the name of your object

class MyObject : public GameObject {
public:
	// Creates the obstacle
	MyObject(sf::Vector2f ipos, sf::Texture texture_);

	// Methods overriden from GameObject
	void draw();
private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<MyObject> MyObjectPtr;