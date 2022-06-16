#pragma once

#include "Engine/GameEngine.h"

class BotExplosion : public AnimatedSprite {
public:
	BotExplosion(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
private:
	void setupBombExplosionAnimation();
	sf::Sound botBoom_;
};

typedef std::shared_ptr<BotExplosion> BotExplosionPtr;