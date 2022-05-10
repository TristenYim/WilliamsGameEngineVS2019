#include "GameObjectTemplate.h"

// Replace "MyObject" with the name of your object
// Change the include to reference the name of the file
// Change the tag

MyObject::MyObject(sf::Vector2f ipos, sf::Texture texture_) {
	sprite_.setTexture(texture_);
	sprite_.setPosition(ipos);
	assignTag("tag");
}

void MyObject::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}