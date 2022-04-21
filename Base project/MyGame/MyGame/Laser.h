#pragma once

#include "Engine/GameEngine.h"

class Laser : public GameObject {
public:
	//Creates a laser
	Laser(sf::Vector2f ipos, float ispeed);

	//Methods overriden from GameObject
	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
private:
	sf::Sprite sprite_;
	float speed;
};

typedef std::shared_ptr<Laser> LaserPtr;