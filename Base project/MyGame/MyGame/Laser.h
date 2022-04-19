#pragma once

#include "Engine/GameEngine.h"

class Laser : public GameObject {
public:
	//Creates a laser
	Laser(sf::Vector2f ipos, float ispeed);

	//Functions overriden from GameObject
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Sprite sprite_;
	float speed;
};

typedef std::shared_ptr<Laser> LaserPtr;