#pragma once

#include "Engine/GameEngine.h"

const int SOLID_TIME = 1500;
const int FADE_OUT_TIME = 500;
const int FADE_IN_TIME = 250;
const int TIME_BUFFER = 1000;
const float ARROW_KEY_DELAY = 1000;
const float ARROW_KEY_SUPER_SPEED_DELAY = 750;

class SelectionBox : public GameObject {
public:
	SelectionBox(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
	void draw();
	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherGameObject);
private:
	sf::Sprite sprite_;

	bool mouseControlsEnabled = false;

	float arrowKeyTimer = 1000;
	float animationTimer = TIME_BUFFER + SOLID_TIME + FADE_OUT_TIME + FADE_IN_TIME;
};

typedef std::shared_ptr<SelectionBox> SelectionBoxPtr;