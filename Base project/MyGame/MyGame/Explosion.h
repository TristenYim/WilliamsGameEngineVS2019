#pragma once

#include "Engine/GameEngine.h"

const bool BoomEnabled = true;

class Explosion : public AnimatedSprite {
public:
	//Creates the explosion
	Explosion(sf::Vector2f ipos);

	//Methods overriden from gameObject
	void update(sf::Time& elapsed);
private:
	void setupExplosionAnimation();

	sf::Sound boom_;
};

typedef std::shared_ptr<Explosion> ExplosionPtr;