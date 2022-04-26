#pragma once

#include "Engine/GameEngine.h"

class Explosion : public AnimatedSprite {
public:
	//Creates the explosion
	Explosion(sf::Vector2f ipos);

	//Methods overriden from gameObject
	void update(sf::Time& elapsed);
private:
	void setupExplosionAnimation();
};

typedef std::shared_ptr<Explosion> ExplosionPtr;