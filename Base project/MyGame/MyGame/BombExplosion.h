#pragma once

#include "Engine/GameEngine.h"

class BombExplosion : public AnimatedSprite {
public:
	BombExplosion(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
private:
	void setupBombExplosionAnimation();
	sf::Sound bombBoom_;
};

typedef std::shared_ptr<BombExplosion> BombExplosionPtr;