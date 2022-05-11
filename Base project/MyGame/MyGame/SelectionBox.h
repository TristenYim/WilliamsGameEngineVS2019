#pragma once

#include "Engine/GameEngine.h"

class SelectionBox : public GameObject {
public:
	SelectionBox(sf::Vector2f ipos);
	void addToPosition(sf::Vector2f additive);
	sf::Vector2f getPosition();

	//void update(sf::Time& elapsed);
	void draw();
	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherGameObject);
private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<SelectionBox> SelectionBoxPtr;