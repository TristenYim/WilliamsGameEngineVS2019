#pragma once

#include "Engine/GameEngine.h"

class BotExplosion : public AnimatedSprite {
public:
	BotExplosion(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
private:
	void setupBombExplosionAnimation();
};

typedef std::shared_ptr<BotExplosion> BotExplosionPtr;