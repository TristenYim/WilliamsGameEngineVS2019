#pragma once

#include "Engine/GameEngine.h"

class RamAnimation : public AnimatedSprite {
public:
	RamAnimation(sf::Vector2f ipos);

	void update(sf::Time& elapsed);
private:
	void setupRamAnimation();
	sf::Sound ramSound_;
};

typedef std::shared_ptr<RamAnimation> RamAnimationPtr;